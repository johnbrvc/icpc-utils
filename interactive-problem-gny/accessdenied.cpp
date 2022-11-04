#include <bits/stdc++.h>

using namespace std;


int main()
{
  string response;
  int length=3;
  string guess;
  for(int i=0;i<20;i++)
  {
    guess="";
    for(int j=0;j<i+1;j++)
      guess+="A";
    cout<<guess<<endl;
    getline(cin,response);
    if(response != "ACCESS GRANTED")
    {
      size_t pos = response.find("("); 
      response = response.substr(pos+1);
      pos = response.find(" ");
      response = response.substr(0,pos);
      int ms=stoi(response);
      if(ms!=5)
      {
        length=i+1;
        break;
      }
    }
    else return 0;
  }

  string chars="";
  for(char a='A';a<='Z';a++)
    chars+=a;
  for(char a='a';a<='z';a++)
    chars+=a;
  for(char a='0';a<='9';a++)
    chars+=a;

  guess="";
  int correct=0;
  while(response!="ACCESS GRANTED")
  for(int j=0;j<chars.length();j++)
  {
    guess=guess.substr(0,correct);
    for(int i=1;i<=length-correct;i++)
    {
      guess+=chars[j];
    }
    
    cout<<guess<<endl;
    getline(cin,response);
    if(response != "ACCESS GRANTED")
    {
      size_t pos = response.find("("); 
      response = response.substr(pos+1);
      pos = response.find(" ");
      response = response.substr(0,pos);
      int ms=stoi(response);
      ms-=5;
      correct=ms/9-1;
    }
    else { cout << "test" << endl; return 0;}
  }

  return 0;
}
