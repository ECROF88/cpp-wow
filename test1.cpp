#include "mycommon.h"

using namespace std;

struct Connection {
  int id;
  explicit Connection(int id) : id(id) {}
};
struct ConnectionBuilderBase {
  virtual Connection connect() = 0;
};
template <bool Ready = false>
struct ConnectionBuilder : ConnectionBuilderBase {
  string port;
  string add;

  bool usessh = false;
  string ss1;
  string ss2;

  std::vector<string> args;
  ConnectionBuilder withport(string port)
  {
    this->port = port;
    return *this;
  }
  ConnectionBuilder<true>& withadd(string add)
  {
    this->add = add;
    return static_cast<ConnectionBuilder<true>&>(static_cast<ConnectionBuilderBase&>(*this));
  }

  ConnectionBuilder<true>& withaddandport(string p)
  {
    auto pos = p.find(':');
    if (pos != string::npos) {
      this->add = p.substr(0, pos);
      this->port = p.substr(pos + 1);
    }
    return static_cast<ConnectionBuilder<true>&>(static_cast<ConnectionBuilderBase&>(*this));
  }
  ConnectionBuilder& withssh(string ss1, string ss2 = "caf")
  {
    usessh = true;
    this->ss1 = ss1;
    this->ss2 = ss2;
    return *this;
  }
  ConnectionBuilder& withargs(std::string args)
  {
    this->args.push_back(args);
    return *this;
  }
  Connection connect()
  {
    // static_assert(Ready, "ADDRESS IS NEEDED TO CONNECT");
    int id = 0;
    return Connection(id);
  }
};

Connection c = ConnectionBuilder<false>().withaddandport("IP_ADDRESS:8080").withargs("arg1").withssh("ssh1").connect();

struct [[nodiscard]] Car {
  int handle;

  Car() {}

  [[nodiscard]] Car&& setBenz(int range) &&
  {
    handle = int(range);
    return move(*this);
  }
  Car(Car&&) = default;
  Car(const Car&) = delete;
};

struct Drinkable;
struct Eatable;
struct FoodVisitor {
  virtual void visit(Eatable* eat) {};
  virtual void visit(Drinkable* drink) {};
  virtual ~FoodVisitor() = default;
};
struct DrinkParams {
  int volume;
};
struct EatParams {
  int weight;
};
struct Food {
  virtual ~Food() = default;
  // virtual Drinkable* asDrinkable() { return nullptr; }
  // virtual Eatable* asEatable() { return nullptr; }
  virtual void accept(FoodVisitor* visitor) = 0;
};
struct Drinkable : virtual Food {
  virtual void drink(DrinkParams params) = 0;
  // Drinkable* asDrinkable() override { return this; }
  void accept(FoodVisitor* visitor) override { visitor->visit(this); }
};

struct Eatable : virtual Food {
  virtual void eat(EatParams params) = 0;
  // Eatable* asEatable() override { return this; }
  void accept(FoodVisitor* visitor) override { visitor->visit(this); }
};

struct Pudding : Drinkable, Eatable {
  void drink(DrinkParams params) override { cout << "drink" << params.volume << endl; }
  void eat(EatParams params) override { cout << "eat" << params.weight << endl; }
  void accept(FoodVisitor* visitor) override
  {
    Eatable::accept(visitor);
    Drinkable::accept(visitor);
  }
};

struct User : FoodVisitor {
  void visit(Eatable* eat) override { eat->eat({1}); }
  void visit(Drinkable* drink) override { drink->drink({2}); }
};
void User_eat(Food* food)
{
  User user1;
  food->accept(&user1);
}
int main()
{
  Car benz = Car().setBenz(100);  // 调用移动而不是拷贝
  // Car().setBenz(100);             // 由于写了[[nodiscard]]，编译器会警告

  Pudding p;
  // p.accept(&run);

  User_eat(&p);
  return 0;
}