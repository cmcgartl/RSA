#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

typedef long long ll; 

ll gcd(ll first, ll second){ //Euclidean algorithm to find gcd
  while(second > 0){
    ll temp = first % second;
    first = second;
    second = temp;
  }
  return first;
}

//euclidean takes in L value and returns d as encryption key
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

//modular exponentation returns base ^ exponent % mod
ll mod_exp(ll base, ll exponent, ll mod) {
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

//calcluates log base 100
int log_100(int value)
{
  return log(value)/log(100);
}

//decrypts message input to output file, uses p and q to determine decryption key
void Decrypt(string input, string output, ll p, ll q)
{
  ll e = 65537;
  ll d = 0;
  ll L = ((p - 1) * (q - 1))/ gcd(p - 1, q - 1);
  ll n = p * q;
  ll x = static_cast<ll>(floor(1+ log_100(n/27)));
  ll C = 0;
  ll M = 0;
  //vector to hold the integer representation of the letters
  vector<int> charNums;
  string message;
  int temp;

  if(L <= e || gcd(e,L) != 1){
    cout << "Error: invalid p and q values" << endl;
    exit (0);
  }
  //finds decryption key d
  d = extendedEuclidean(L);
  ifstream ifile(input);
  if(ifile.fail()){
    cout << "Error: invalid input file" << endl;
    exit (0);
  }
  ofstream ofile(output);
  if(ofile.fail()){
    cout << "Error: invalid output file" << endl;
    exit (0);
  }
  //reads in each long long from encrypted file
  while(ifile >> C){
    M = mod_exp(C, d, n);
    //converts each number to x integer representations of the letters
    for(int i = x; i > 0; i--){
      //temp = the first two digits of the number
      temp = M / (pow(10, (i * 2) - 2));
      //adds each to the integer representation vector
      charNums.push_back(temp);
      //removes the first two digits from M
      M -= temp * (pow(10, (i * 2) - 2));
    }
  }
  //walks through charNums, converts each int to a char, prints to output
  for(unsigned int i = 0; i < charNums.size(); i++){
    if(charNums[i] != 0){
    char letter = 'a' + charNums[i] - 1;
    ofile << letter;
  }
  else{
    ofile << ' ';
  }

  }
}

//takes in n as p*q, output file, and message
void Encrypt(long long n, string output, string temp){

    ll e = 65537;
    ofstream ofile(output);
    if(ofile.fail()){
      cout << "Error: invalid output file" << endl;
      exit(0);
    }
    ll x = static_cast<ll>(floor(1+ log_100(n/27)));
    for(size_t i = 0; i < temp.length(); i += x){
      ll M = 0;
      //count determines how many times M is incremented
      int count = 0;
      //walks through x letters of each word, converts the letter to a two digit
      //representation, add that to M, then print M to output
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
          //if M has ben incremented less than x times, M is not long enough
          //and must be resized to 2*x digits
          if(x - count != 0){
              M = M * pow(10, (2 * (x -count)));
          }
          count = 0;
          if((i + x) < temp.length()){
          ofile << mod_exp(M, e, n) << " ";
          }
          else{
            ofile << mod_exp(M, e, n);
          }
    }
    ofile << std::endl;
    ofile.close();
}

int main(int argc, char* argv[]){
  if(argc != 3){
    cout << "invalid command arguments" << endl;
    exit(0);
  }
ll p = stoll(argv[1]);
ll q = stoll (argv[2]);
ll n = p * q;
string command;
string input;
string output;
string message;
//ensures n >= 27
while(n < 27){
  cout << "error: n is less than 27, please enter 2 new primes" << endl;
  cin >> p;
  cin >> q;
  n = p * q;
}
//reads in command then reads in appropriate data
//and calls appropriate functions
cout << "Enter Command" << endl;
cin >> command;
if(command == "EXIT"){
  exit(0);
}
else if(command == "DECRYPT"){
  cout << "Enter Two Files:" << endl;
  cin >> input;
  cin >> output;
  Decrypt(input, output, p, q);
}
else if(command == "ENCRYPT"){
  cout << "Enter output filename, n value, and message" << endl;
  cin >> output;
  cin >> n;
  //converts the message to a string
  getline(cin, message);
  message = message.substr(1);
  ifstream ifile(message);
  //if the message is the name of a text file, set message = to its contents
  if(!ifile.fail()){
    getline(ifile,message);
  }
  Encrypt(n, output, message);
}
return 0;
}