export module aoc_utils;
import std;

namespace aoc_utils {

export auto read_file(std::string filename) -> std::string {
  std::ifstream ifstrm(filename, std::ios::binary);
  if (!ifstrm.is_open()) {
    throw std::runtime_error("Failed to open " + filename);
  }

  ifstrm.seekg(0, std::ios::end);
  const auto size = ifstrm.tellg();
  ifstrm.seekg(0, std::ios::beg);

  const auto read_into = [](std::istream &istrm) {
    return [&istrm](char *buf, std::size_t n) {
      istrm.read(buf, n);
      return static_cast<std::size_t>(istrm.gcount());
    };
  };

  std::string out;
  out.resize_and_overwrite(static_cast<std::size_t>(size), read_into(ifstrm));
  return out;
}

export auto get_line_view(std::string_view sv)
    -> std::generator<std::string_view> {
  const auto drop_trailing_cr = [](std::string_view line) -> std::string_view {
    if (!line.empty() && line.back() == '\r')
      return line.substr(0, line.size() - 1);
    return line;
  };

  auto line_begin = 0uz;
  while (line_begin < sv.size()) {
    const auto line_end = sv.find('\n', line_begin);

    if (line_end == std::string_view::npos) {
      const auto line = sv.substr(line_begin);
      co_yield drop_trailing_cr(line);
      break;
    }

    const auto line = sv.substr(line_begin, line_end - line_begin);
    co_yield drop_trailing_cr(line);
    line_begin = line_end + 1;
  }
}

} // namespace aoc_utils
