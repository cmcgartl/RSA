#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

typedef long long ll;

ll log_100(ll value){
    return log(value)/log(100);
}

ll mod_exp(ll base, ll exponent, ll mod) {

{
ll x = 1;
ll divider = 1;
ll r = base % mod;
while(exponent / divider){
    if((exponent/divider) % 2){
        x = (x*r) % mod;
    }
    r = (r*r) % mod;
    divider *=2;
}
return x;
}
}
void Encrypt(long long n, string input, string output){

    string temp;
    ll e = 65537;
    ll C = 0;
    ifstream ifile(input);
    getline(ifile,temp);
    getline(ifile,temp);
    ofstream ofile(output);
    

    ll x = static_cast<ll>(floor(1+ log_100(n/27)));
    for(size_t i = 0; i < temp.length(); i += x){
    ll M = 0;
    int count = 0;
        for(unsigned int j = 0; j < x && i + j < temp.length(); j++){
            if(temp[i + j] == ' '){
                M *= 100;
                count++;
            }
            else{
                M = M * 100 + (temp[i + j] - 'a' + 1);
                count++;
                }
            }
            if(x - count != 0){
                M = M * pow(10, (2 * (x -count)));
            }
            count = 0;
            ofile << mod_exp(M, e, n) << " ";
            cout << "First M used: " << M << endl;
    }
}

ll gcd(ll first, ll second){

  while(second > 0){
    ll temp = first % second;
    first = second;
    second = temp;
  }
  return first;
}

ll extendedEuclidean(ll L)
{
  ll s = 0;
  ll old_s  = 1;
  ll t = 1;
  ll old_t = 0;
  ll r = 65537;
  ll old_r = L;
  while(r != 0){
  ll quotient = old_r / r; //4
  ll temp = r;
  r = old_r - quotient * r;
  old_r = temp;
  temp = s;
  s = old_s - quotient * s;
  old_s = temp;
  temp = t;
  t = old_t - quotient * t;
  old_t = temp; // 13
  }
  while (old_t < 0){
    old_t += 65537*L;
  }
  return old_t;
}

int main(int argc, char* argv[])
{
    string message = "fight on";
    message = message.substr(1);
    cout << message << endl;
    return 0;
}   
