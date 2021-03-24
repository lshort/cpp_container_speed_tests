#include <boost/container/flat_map.hpp>
#include <boost/container/static_vector.hpp>
#include <map>
#include <forward_list>
#include <chrono>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <numeric>
#include <random>

const int SIZE = 100'000'000; 

// function by Rainer Grimm
template <typename T>
void accumContainer(const T& t, const std::string& cont){
  
  std::cout << std::fixed << std::setprecision(10);

  auto begin= std::chrono::steady_clock::now();
  std::size_t res = std::accumulate(t.begin(), t.end(), 0LL);
  std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
  std::cout << cont << " with std::accumulate" <<  std::endl;
  std::cout << "accumulate time: " << last.count() << std::endl;
  std::cout << "res: " << res << std::endl;
  std::cout << std::endl;
 
  std::cout << std::endl;
     
}

template <typename T>
void sumContainer(const T& t, const std::string& cont){
  
   std::cout << std::fixed << std::setprecision(10);

   auto begin= std::chrono::steady_clock::now();
   size_t res{0};
   for (int n : t){
      res += n;
   }
   std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
   std::cout << cont << " foreach loop" <<  std::endl;
   std::cout << "sum time: " << last.count() << std::endl;
   std::cout << "res: " << res << std::endl;
   std::cout << std::endl;
 
   std::cout << std::endl;
     
}

template <typename T>
void sumContainerData(const T& t, const std::string& cont){
  
   std::cout << std::fixed << std::setprecision(10);

   auto begin= std::chrono::steady_clock::now();
   size_t res{0};
   for (int i=0; i < SIZE; ++i){
      res += t[i];
   }
   std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
   std::cout << cont << " loop over container indices" <<  std::endl;
   std::cout << "sum time: " << last.count() << std::endl;
   std::cout << "res: " << res << std::endl;
   std::cout << std::endl;
 
   std::cout << std::endl;
     
}

template <typename T>
void sumContainerDataPtr(const T& t, const std::string& cont){
  
   std::cout << std::fixed << std::setprecision(10);

   auto begin= std::chrono::steady_clock::now();
   const int* ptr = t.data();
   size_t res{0};
   for (int i=0; i < SIZE; ++i){
      res += ptr[i];
   }
   std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
   std::cout << cont << " loop over indices into .data() pointer" <<  std::endl;
   std::cout << "sum time: " << last.count() << std::endl;
   std::cout << "res: " << res << std::endl;
   std::cout << std::endl;
 
   std::cout << std::endl;
     
}

void sumCArray(int* t, const std::string& cont){
  
   std::cout << std::fixed << std::setprecision(10);

   auto begin= std::chrono::steady_clock::now();
   size_t res{0};
   for (int i=0; i < SIZE; ++i){
      res += t[i];
   }
   std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
   std::cout << cont <<  std::endl;
   std::cout << "sum time: " << last.count() << std::endl;
   std::cout << "res: " << res << std::endl;
   std::cout << std::endl;
 
   std::cout << std::endl;
     
}


int main(){
    
    std::cout << std::endl;
    
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<int> dist(0, 100);
    std::vector<int> randNumbers;
    randNumbers.reserve(SIZE);
    for (int i=0; i < SIZE; ++i){
        randNumbers.push_back(dist(engine));
    }
    
    auto begin= std::chrono::steady_clock::now();
    std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
    {
      begin = std::chrono::steady_clock::now();
      std::vector<int> myVec(randNumbers.begin(), randNumbers.end());
      std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
      std::cout << "************ Time to create and fill std::vector<int,SIZE>: " << last.count() << std::endl;
      accumContainer(myVec,"std::vector<int>");
      sumContainer(myVec,"std::vector<int>");
      sumContainerData(myVec,"std::vector<int>");
      sumContainerDataPtr(myVec,"std::vector<int>");
      sumCArray(myVec.data(),"std::vector<int>.data()");
    }

    {
       begin = std::chrono::steady_clock::now();
       boost::container::static_vector<int, SIZE> myVec(randNumbers.begin(), randNumbers.end());
       std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
       std::cout << "************ Time to create and fill boost::container::static_vector<int,SIZE>: " << last.count() << std::endl;
       accumContainer(myVec,"boost::container::static_vector<int>");
    }

    {
       begin = std::chrono::steady_clock::now();
       std::array<int, SIZE> stdArray;
       int counter = 0;
       int next_counter = 10;
       for (int i=0; i < SIZE; ++i){
          stdArray[i] = randNumbers[i];
       }
       std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
       std::cout << "************ Time to create and fill std::array<int>: " << last.count() << std::endl;
       accumContainer(stdArray,"std::array<int>");  // (6)
    }

    {
       begin = std::chrono::steady_clock::now();
       int stackArray[SIZE];
       int counter = 0;
       int next_counter = 10;
       for (int i=0; i < SIZE; ++i){
          stackArray[i] = randNumbers[i];
       }
       std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
       std::cout << "************ Time to create and fill stack C array: " << last.count() << std::endl;
       sumCArray(stackArray,"stack C array<int>");  // (7)
    }

    {
       begin = std::chrono::steady_clock::now();
       int *heapArray = (int*)malloc(sizeof(int)*SIZE);
       int counter = 0;
       int next_counter = 10;
       for (int i=0; i < SIZE; ++i){
          heapArray[i] = randNumbers[i];
       }
       std::chrono::duration<double> last=  std::chrono::steady_clock::now() - begin;
       std::cout << "************ Time to create and fill heap C array: " << last.count() << std::endl;
       sumCArray(heapArray,"heap C array<int>");  // (8)
    }
  
}


