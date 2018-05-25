#include <unordered_map>
#include <iostream>
#include <list>
#include <string>

using namespace std;

typedef int c_id;
typedef string c_element;

struct Lock{
  enum Permision : bool{
    Shared = false,
    Exclusive = true
  };
  Permision permision;
  bool granted;
  c_id id;
  //Lock(Permision p): permision(p) {}//Constructor Lock
};

typedef list<Lock> Lockes;
typedef unordered_map<c_element, Lockes> LockTable;

class LockManagement{
private:
  LockTable Table;
  void UpdateBlock(Lockes::iterator& it_list, LockTable::iterator it_hash, c_id transaction){
    if (it_list == it_hash->second.end())
      return;
    for(; it_list != it_hash->second.end() ;++it_list){
      if (it_list->id == transaction){
        it_list->granted = true;
        return;
      }
    }
  }
public:
  LockManagement(){} //Constructor
  bool LockBlock(c_element variable, c_id transaction, Lock::Permision type){
    auto it = Table.find(variable);
    if(it == Table.end()){
      Table[variable].push_back(Lock{.permision = type, .granted = true, .id = transaction});
      return 1;
    }
    if( it->second.rbegin()->granted == false)
      return 0;
    else{
      if ( it->second.rbegin()->permision != type)
        Table[variable].push_back(Lock{.permision = type, .granted = false, .id = transaction});
      else
        Table[variable].push_back(Lock{.permision = type, .granted = true, .id = transaction});
      return 1;
    }
  }
  void UnlockBlock(c_element variable, c_id transaction){
    auto it = Table.find(variable);
    if(it == Table.end())
      return;
    for(auto i = it->second.begin(); i != it->second.end() ; ++i){
      if( i->granted == 0)
        return;
      if( i->id == transaction){
        it->second.erase(i,it,transaction);
        UpdateBlock(i);
        return;
      }
    }
  }
  ~LockManagement() = default;
};

main(){
  LockManagement Table;
}
