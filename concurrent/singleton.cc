struct Singleton {

  static Singleton& instance();

private:
  Singleton( const Singleton& rhs ) = delete;
  const Singleton& operator=( const Singleton& rhs ) = delete;
  // move ctor/assi will be supressed 显示delet 没必要
  Singleton( const Singleton&& rhs ) = delete;
  const Singleton& operator=( const Singleton&& rhs ) = delete;

  Singleton();
  ~Singleton()

  static std::atomic<size_t> s_refs;
};

Singleton& Singleton::instance( ) {
  static Singleton instance{};
  return instance;
}

Singleton::Singleton() {
  std::cout << "Constructing Singleton" << std::endl;
}

Singleton::~Singleton() {
  std::cout << "Destroying Singleton" << std::endl;
}

// eg.
Singleton::instance()
Singleton& s{Singleton::instance()};