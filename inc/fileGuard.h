#pragma once

template <typename T>
class FileGuard {
private:
  T _fstream;

public:
  FileGuard(const std::string &filePath, std::ios_base::openmode mode);
  ~FileGuard();
  FileGuard(const FileGuard&) = delete;
  FileGuard& operator=(const FileGuard&) = delete;
  FileGuard(FileGuard&&) = delete;
  FileGuard& operator=(FileGuard&&) = delete;

  T& get() { return _fstream; }
};

template<typename T>
inline FileGuard<T>::FileGuard(const std::string &filePath, std::ios_base::openmode mode)
  : _fstream{} {
  _fstream.open(filePath, mode);
}

template<typename T>
inline FileGuard<T>::~FileGuard() {
  if (_fstream.is_open()) {
    _fstream.close();
  }
}

