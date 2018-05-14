#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <string>
#include <list>

using namespace std;

typedef int c_key;

struct OBJ{
  map <int , c_key> instances;
  int pos;
  c_key* key;
  vector<int> changes;
  OBJ(): pos(0) {}
  OBJ(c_key* k): key(k), pos(0) {}
};

class Transaction{
public:
  list<string> instructions;
  Transaction() {}
  void fill(){
    cout << "Type: read(X) for read value from disk" << '\n';
    cout << "Type: sum(X,Y) for add Y to X" << '\n';
    cout << "Type: rest(X,Y) for rest Y to X " << '\n';
    cout << "Type: write(X) for update the value" << '\n';
    cout << "Type: display(X) for show the value" << '\n';
    while(true){
      string line;
      cin>>line;
      if(line == "exit")
        break;
      else
        this->instructions.push_back(line);
    }
  }
};

class ControlTransaction{
private:
  map<char, OBJ*> container;
  void Processline(string& s){
    if (s.substr(0,4) == "read")
      read(s);
    else if (s.substr(0,3) == "sum")
      sum(s);
    else if (s.substr(0,4) == "rest")
      rest(s);
    else if (s.substr(0,5) == "write")
      write(s);
    else if (s.substr(0,7) == "display")
      display(s);
    else
      return;
  }
  void read(string& s){
    char k = s[5];
    auto it = this->container[k];
    it->instances[it->pos] = *(it->key);
    it->changes.push_back(it->pos);
    ++(it->pos);
  }
  void sum(string& s){
    char k = s[4];
    auto it = this->container[k];
    int n;
    stringstream ss(s.substr(6,s.size()-1));
    ss >> n;
    if(it->changes.empty()){
      std::cout << "Cannot operate without read any variable" << '\n';
      return;
    }
    it->instances[*(it->changes.end())] += n;
    it->changes.pop_back();
  }
  void rest(string& s){
    char k = s[5];
    auto it = this->container[k];
    int n;
    stringstream ss(s.substr(7,s.size()-1));
    ss >> n;
    if(it->changes.empty()){
      std::cout << "Cannot operate without read any variable" << '\n';
      return;
    }
    it->instances[*(it->changes.end())] -= n;
    it->changes.pop_back();
  }
  void write(string& s){
    char k = s[6];
    auto it = this->container[k];
    if(it->instances.empty()){
      std::cout << "Cannot write on disk without read any variable" << '\n';
      return;
    }

    *(it->key) = it->instances.end()->second;
    it->instances.erase(it->pos);
    --it->pos;
  }
  void display(string& s){
    char k = s[8];
    cout << *(this->container[k]->key) << '\n';
  }
  void fillMap(vector<char>& v){
    for(auto it = v.begin(); it != v.end(); ++it){
      c_key *n =new c_key(100);
      OBJ *o = new OBJ(n);
      this->container[*it] = o;
    }
  }
public:
  ControlTransaction(vector<char>& v){
    fillMap(v);
  }
  ControlTransaction(Transaction& t1, Transaction& t2, vector<char>& v){
    fillMap(v);
    ProcessTransaction(t1,t2);
  }
  void ProcessTransaction(Transaction& t1, Transaction& t2){
    for(auto it = t1.instructions.begin(); it != t1.instructions.end(); ++it)
      Processline(*it);
    for(auto it = t2.instructions.begin(); it != t2.instructions.end(); ++it)
      Processline(*it);
  }
};

main(){
  Transaction t1,t2;
  t1.fill();
  t2.fill();
  vector<char> v = {'x','y','z'};
  ControlTransaction c(t1,t2,v);
  cout << "end" << '\n';
}
