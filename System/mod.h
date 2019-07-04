#ifndef MOD_H_INCLUDED
#define MOD_H_INCLUDED

//get mod of passed number
namespace
{
    int mod(int number)
    {
        if(number<0)
        {
            return number*=-1;
        }
        else
        {
            return number;
        }
    }
    
    float mod(float number)
    {
        if(number<0.0f)
        {
            return number*=-1;
        }
        else
        {
            return number;
        }
    }
}


#endif // MOD_H_INCLUDED
