#include <iostream>
#include <string>
#include <utility>
#include <memory>




struct AllocateMetrics
{
    uint32_t TotalAllocated;
    uint32_t TotalFreeing; 

    uint32_t GetMemoryUsage()
    {
        return TotalAllocated - TotalFreeing;
    }
};

static AllocateMetrics s_AllocateMetrics;

void* operator new(size_t size)
{
    s_AllocateMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void* memory , size_t size)
{
    s_AllocateMetrics.TotalFreeing += size;
    free(memory);
}


void PrintMemoryUsage()
{
    std::cout << "memory usage : " << s_AllocateMetrics.GetMemoryUsage() << std::endl;
}

struct Random
{
    int x,y,z;
};
int main()
{
    PrintMemoryUsage();
    {
        std::unique_ptr<Random> rand = std::make_unique<Random>();
        PrintMemoryUsage();
    }
    PrintMemoryUsage();
}


