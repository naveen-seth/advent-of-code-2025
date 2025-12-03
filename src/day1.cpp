import std;
import aoc_utils;
import flux;

using namespace std::literals;

constexpr auto parse_rotation(std::string_view sv) -> int {
  const auto to_int = [](std::string_view s) -> std::optional<int> {
    auto value = 0;
    if (std::from_chars(s.data(), s.data() + s.size(), value).ec == std::errc{})
      return value;
    else
      return std::nullopt;
  };

  const auto sign = sv.front() == 'L' ? -1 : +1;
  const auto number_sv = sv.substr(1);
  return to_int(number_sv)
      .transform([=](auto i) { return i * sign; })
      .value_or(0);
}

constexpr auto period = 100;

constexpr auto apply_rotation(int pos, int step) -> int {
  const auto rem = (pos + step) % period;
  return rem < 0 ? rem + period : rem;
}

constexpr auto count_zero_visits(int pos, int step) -> int {
  auto count = std::abs(step) / period;
  const auto rem = step % period;

  if (rem == 0 || pos == 0)
    return count;

  const auto next_pos = pos + rem;
  if (next_pos >= period || next_pos <= 0)
    ++count;

  return count;
}

auto main() -> int {
  constexpr auto input = "inputs/day1.dat"sv;
  const auto contents = aoc_utils::read_file(std::string(input));

  constexpr auto start_position = 50;
  const auto steps = flux::from_range(aoc_utils::get_line_view(contents))
                         .map(parse_rotation)
                         .to<std::vector<int>>();
  const auto positions =
      flux::chain(std::array{start_position},
                  flux::from_range(steps).scan(apply_rotation, start_position))
          .to<std::vector<int>>();

  const auto part1 = flux::from_range(positions).count_eq(0);
  const auto part2 =
      flux::zip(flux::from_range(positions), flux::from_range(steps))
          .map([](auto p) {
            auto [pos, step] = p;
            return count_zero_visits(pos, step);
          })
          .sum();

  std::println("day 1, part 1: {}", part1);
  std::println("day 1, part 2: {}", part2);
}
