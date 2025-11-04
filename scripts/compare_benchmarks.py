#!/usr/bin/env python3
"""
compare_benchmarks.py - Compare two benchmark results and detect regressions

This script compares two JSON benchmark outputs and reports performance
regressions and improvements.
"""

import json
import sys
from pathlib import Path
from typing import Dict, List, Tuple


class Color:
    """ANSI color codes for terminal output"""
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[1;33m'
    BLUE = '\033[0;34m'
    NC = '\033[0m'  # No Color


def load_benchmark(filename: Path) -> Dict:
    """Load benchmark results from JSON file"""
    try:
        with open(filename) as f:
            data = json.load(f)
        return {b['name']: b for b in data['benchmarks']}
    except FileNotFoundError:
        print(f"{Color.RED}Error: File not found: {filename}{Color.NC}")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"{Color.RED}Error: Invalid JSON in {filename}: {e}{Color.NC}")
        sys.exit(1)
    except KeyError as e:
        print(f"{Color.RED}Error: Missing key in benchmark data: {e}{Color.NC}")
        sys.exit(1)


def format_time(nanoseconds: float) -> str:
    """Format time in appropriate units"""
    if nanoseconds < 1000:
        return f"{nanoseconds:.2f} ns"
    elif nanoseconds < 1000000:
        return f"{nanoseconds / 1000:.2f} us"
    elif nanoseconds < 1000000000:
        return f"{nanoseconds / 1000000:.2f} ms"
    else:
        return f"{nanoseconds / 1000000000:.2f} s"


def compare_benchmarks(
    baseline_file: Path,
    current_file: Path,
    threshold: float = 0.05
) -> int:
    """
    Compare two benchmark runs and detect regressions

    Args:
        baseline_file: Path to baseline benchmark JSON
        current_file: Path to current benchmark JSON
        threshold: Regression threshold (0.05 = 5%)

    Returns:
        0 if no regressions, 1 if regressions detected
    """
    baseline = load_benchmark(baseline_file)
    current = load_benchmark(current_file)

    regressions: List[Tuple[str, float, float, float]] = []
    improvements: List[Tuple[str, float, float, float]] = []
    new_benchmarks: List[str] = []
    removed_benchmarks: List[str] = []

    # Find regressions and improvements
    for name, current_bench in current.items():
        if name not in baseline:
            new_benchmarks.append(name)
            continue

        baseline_time = baseline[name]['real_time']
        current_time = current_bench['real_time']

        # Calculate percentage change
        change = (current_time - baseline_time) / baseline_time

        if change > threshold:
            regressions.append((name, baseline_time, current_time, change))
        elif change < -threshold:
            improvements.append((name, baseline_time, current_time, change))

    # Find removed benchmarks
    for name in baseline:
        if name not in current:
            removed_benchmarks.append(name)

    # Print header
    print(f"\n{Color.BLUE}{'=' * 70}{Color.NC}")
    print(f"{Color.BLUE}Benchmark Comparison Report{Color.NC}")
    print(f"{Color.BLUE}{'=' * 70}{Color.NC}\n")

    print(f"Baseline: {baseline_file}")
    print(f"Current:  {current_file}")
    print(f"Threshold: {threshold * 100:.1f}%\n")

    # Print improvements
    if improvements:
        print(f"\n{Color.GREEN}🎉 IMPROVEMENTS ({len(improvements)} benchmarks):{Color.NC}")
        print(f"{'Benchmark':<50} {'Baseline':<15} {'Current':<15} {'Change':<10}")
        print("-" * 90)

        for name, baseline_time, current_time, change in sorted(
            improvements, key=lambda x: x[3]
        ):
            change_pct = abs(change) * 100
            print(
                f"{name:<50} "
                f"{format_time(baseline_time):<15} "
                f"{format_time(current_time):<15} "
                f"{Color.GREEN}-{change_pct:.1f}%{Color.NC}"
            )

    # Print regressions
    if regressions:
        print(f"\n{Color.RED}⚠️  REGRESSIONS ({len(regressions)} benchmarks):{Color.NC}")
        print(f"{'Benchmark':<50} {'Baseline':<15} {'Current':<15} {'Change':<10}")
        print("-" * 90)

        for name, baseline_time, current_time, change in sorted(
            regressions, key=lambda x: x[3], reverse=True
        ):
            change_pct = change * 100
            print(
                f"{name:<50} "
                f"{format_time(baseline_time):<15} "
                f"{format_time(current_time):<15} "
                f"{Color.RED}+{change_pct:.1f}%{Color.NC}"
            )

    # Print new benchmarks
    if new_benchmarks:
        print(f"\n{Color.YELLOW}📊 NEW BENCHMARKS ({len(new_benchmarks)}):{Color.NC}")
        for name in sorted(new_benchmarks):
            print(f"  + {name}")

    # Print removed benchmarks
    if removed_benchmarks:
        print(f"\n{Color.YELLOW}🗑️  REMOVED BENCHMARKS ({len(removed_benchmarks)}):{Color.NC}")
        for name in sorted(removed_benchmarks):
            print(f"  - {name}")

    # Print summary
    print(f"\n{Color.BLUE}{'=' * 70}{Color.NC}")
    print(f"{Color.BLUE}SUMMARY{Color.NC}")
    print(f"{Color.BLUE}{'=' * 70}{Color.NC}\n")

    total_compared = len(baseline) - len(removed_benchmarks)
    unchanged = total_compared - len(regressions) - len(improvements)

    print(f"Total benchmarks compared: {total_compared}")
    print(
        f"{Color.GREEN}Improvements: {len(improvements)}{Color.NC} "
        f"({len(improvements) / total_compared * 100:.1f}%)"
    )
    print(
        f"{Color.RED}Regressions:  {len(regressions)}{Color.NC} "
        f"({len(regressions) / total_compared * 100:.1f}%)"
    )
    print(
        f"Unchanged:    {unchanged} "
        f"({unchanged / total_compared * 100:.1f}%)"
    )

    if new_benchmarks:
        print(f"{Color.YELLOW}New:          {len(new_benchmarks)}{Color.NC}")
    if removed_benchmarks:
        print(f"{Color.YELLOW}Removed:      {len(removed_benchmarks)}{Color.NC}")

    print()

    # Determine exit code
    if regressions:
        print(f"{Color.RED}❌ Performance regressions detected!{Color.NC}\n")
        return 1
    elif improvements:
        print(f"{Color.GREEN}✅ Performance improved or unchanged{Color.NC}\n")
        return 0
    else:
        print(f"{Color.GREEN}✅ No significant performance changes{Color.NC}\n")
        return 0


def main():
    """Main entry point"""
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <baseline.json> <current.json>")
        print()
        print("Compare two benchmark JSON files and detect performance regressions.")
        print()
        print("Example:")
        print(f"  {sys.argv[0]} baseline.json current.json")
        sys.exit(1)

    baseline_file = Path(sys.argv[1])
    current_file = Path(sys.argv[2])

    # Run comparison with 5% threshold
    exit_code = compare_benchmarks(baseline_file, current_file, threshold=0.05)
    sys.exit(exit_code)


if __name__ == '__main__':
    main()
