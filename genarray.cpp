#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#define nMAX 5000000
#define nmod 8

#include<bits/stdc++.h> 

typedef std::pair<int,int> SDATA;

std::vector<SDATA >  a;

unsigned int seed;
unsigned int seed2;
int n;

int main(int argc,char* argv[])
{
  int i;
  int option;
  std::string s1,s2;
  seed2=1027;
  seed=31027;
  if (argc>1)
  {
	  s1=argv[1];
	  std::stringstream is1(s1); 
	  is1>>n;
  }
  else n=4500000;
  if (argc>2)
    {
	    
	  s2=argv[2];
	  std::stringstream is2(s2); 
	    
	  is2 >> option; 
    }	    
  else option=0;
  std::cout <<"n="<<n<<" option="<<option<<"\n";
  std::cout <<"Array Length is "<<n<<" \n";
  switch (option)
  {
	  case 1:
		  {
                   for (i=0;i<n;i++) a.push_back(std::make_pair<int,int>(i+1,0)); 
		   break;
		  }

	  case 2:
		  {
		   for (i=0;i<n;i++)  
		   a.push_back(std::make_pair(n+1-i,0));
	           break;
		  }
	  case 3:
		  {
		    a.resize(n);
			  for (i=n/2-1;i>=0;i--)
                             {
			       
                              a[2*i].first=2*i+2;
                              a[2*i].second=0;
		              a[2*i+1].first=2*i+1;	  
		              a[2*i+1].second=0;	  
			     } 
			     if (n%2){
			              a[n-1].first=n+1;
                                      a[n-1].second=0;
			             } 
			  break;
		  }
	  case 4:
		  {
		    a.resize(n);
			  for (i=n-1;i>=0;i--)
                             {
                              if (i% nmod)
			        { 
				  a[i].first=i;
				  a[i].second=0;
				}
		              else 
			       {
			        //a[i].first=nmod+nmod/(i+1); 
			        a[i].second=0; 
			       }
			     } 
			  break;
		  }
	  case 5:
		  {
		    a.resize(n);
			  for (i=0;i<n;i+=2)
                             {
                              if ((i% nmod)) 
			        {
				 a[i].first=i;
				 a[i].second=0;
				 (i<n-1)?(a[i+1].first=i+1,
				 a[i+1].second=0):0;
				} 
		              else 
			        {
				  a[i].first=i+1;
				  a[i].second=0;
				  (i<n-1)?(a[i+1].first=i,
				  a[i+1].second=0):0;
				} 
			     } 
			  break;
		  }
          case 6:{
	           a.resize(n);
		   for (i=0;i<n;i++)
		   {
			   a[i].first=i/10;
			   a[i].second=rand_r(&seed2)%20;
		   }
		   break;
                 }			 
          case 7:{
	           a.resize(n);
		   for (i=0;i<n;i++)
		   {
		   if (i%2)
		     {	   a[i].first=i;
			   a[i].second=0;
		     }
		     else
		     {	   a[i].first=n+3-i;
			   a[i].second=0;
		     }
		   }  
		   break;
                 }
	  default:
		  {
		   a.resize(n); 
                   for (i=0;i<n;i++)
                      {
	               a[i].first=rand_r(&seed);
	               a[i].second=rand_r(&seed);
	              } 
		   break;
		  }
   
  }

  for (i=0;i<n;i++)
	  std::cout<<"("<< a[i].first <<","<< a[i].second <<") ";
   std::cout<<std::endl;
  return 0;

}
