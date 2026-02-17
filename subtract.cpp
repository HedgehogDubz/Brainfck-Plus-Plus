#include <iostream>
#include <vector>
void mov_right();
bool mov_left();
void add();
void sub();
void save();
void load();
void print();
int p = 0;
int s = 0;
std::vector<int> a = {0};
int main(){
    
a[p] = 18;
mov_right();
a[p] = 45;
while (a[p] != 0) {
sub();
if(mov_left()){return 1;}
sub();
mov_right();
}
if(mov_left()){return 1;}
print();

    return 0;
}  
void mov_right(){
    p++;
    if(p >= a.size()){
        a.push_back(0);
    }
}
bool mov_left(){
    p--;
    if(p < 0){
        std::cerr << "\033[31m" << "ERROR pointer below 0" << "\033[0m" << std::endl;
        return true;
    }
    return false;
}
void add(){
    a[p]++;
}
void sub(){
    a[p]--;
}
void save(){
    s = a[p];
}
void load(){
    a[p] = s;
}
void print(){
    std::cout << a[p];
}