//
//	Class: Executor
//	Description: Executor is a class that executes a function at specific times/intervals
//               by using human language and a function pointer.
//
//  Usage:
//               Executor execute;
//               execute.setAction(this, &ClassName::memberFunction);
//               execute.setInterval("twice in 4 times");
//
//               -- call the funcor methode
//               execute(); // do nothing
//               execute(); // execute function..
//               execute(); // do nothing
//               execute(); // execute function ..
//
//               -- but you can also specify time intervals
//               execute.setInterval("four times a day");
//               execute.setInterval("once a day");
//               execute.setInterval("twice in 10 minutes");
//               execute.setInterval("thrice in 120 functions calls");
//
//
//  Created:     28/11/2014
//  Author:      Cédric Verstraeten
//  Mail:        hello@cedric.ws
//	Website:	 www.cedric.ws
//
//  The copyright to the computer program(s) herein
//  is the property of cedric.ws, Belgium.
//  The program(s) may be used and/or copied .
//
/////////////////////////////////////////////////////

#ifndef __Executor_H_INCLUDED__   // if Executor.h hasn't been included yet...
#define __Executor_H_INCLUDED__   // #define this so the compiler knows it has been included

#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
#include <sstream>
#include <map>
#include <vector>

namespace kerberos
{
    enum IntervalType {
        SEQUENCE_INTERVAL,
        TIME_INTERVAL
    };
    
    class ExecutorType
    {
        protected:
            std::vector<std::pair<int, IntervalType> > integers;
        public:
            typedef std::vector<std::pair<int, IntervalType> > IntegerTypeArray;
            virtual bool operator()() = 0;
    };
    
    class SequenceInterval : public ExecutorType
    {
        private:
            int m_count;
            int m_times;
            int m_boundery;
            int m_increase;
            
        public:
            SequenceInterval(IntegerTypeArray & integers);
            bool operator()();
    };
    
    class TimeInterval : public ExecutorType
    {
        public:
            TimeInterval(IntegerTypeArray & integers);
            bool operator()();
    };

	template<>
    class Executor
    {
        private:
            bool (*m_func)();
            ExecutorType * m_execute;
            std::map<std::string, std::pair<int, IntervalType> > m_humanTime;
        
            // private functions
            void parse(std::string & sentence);
        
        public:
            Executor();
            ~Executor();
            Executor(std::string & sentence, bool (*func)());
            Executor(char * sentence, bool (*func)());
        
            void setAction(bool (*func)());
            void setInterval(std::string & sentence);
            void setInterval(char * sentence);
            void initialize();
            bool operator()();
    };

    
    template<class T>
    class Executor
    {
        private:
            T * m_obj;
            bool (T::*m_func)();
            ExecutorType * m_execute;
            std::map<std::string, std::pair<int, IntervalType> > m_humanTime;
        
            // private functions
            void parse(std::string & sentence);
        
        public:
            Executor();
            ~Executor();
            Executor(std::string & sentence, T * obj, bool (T::*func)());
            Executor(char * sentence, T * obj, bool (T::*func)());
        
            void setAction(T * obj, bool (T::*func)());
            void setInterval(std::string & sentence);
            void setInterval(char * sentence);
            void initialize();
            bool operator()();
    };

    template<class T>
    Executor<T>::Executor(){}
	template<int>
    Executor::Executor(){}
    
    template<class T>
    Executor<T>::~Executor()
    {
        if(m_execute!=0)
        {
            delete m_execute;
        }
    }
	template<int>
    Executor::~Executor()
    {
        if(m_execute!=0)
        {
            delete m_execute;
        }
    }
    
    template<class T>
    Executor<T>::Executor(std::string & sentence, T * obj, bool (T::*func)())
    {
        parse(sentence);
        m_obj = obj;
        m_func = func;
    }
	template<int>
    Executor::Executor(std::string & sentence, bool (*func)())
    {
        parse(sentence);
        m_func = func;
    }
    
    template<class T>
    void Executor<T>::setAction(T * obj, bool (T::*func)())
    {
        m_obj = obj;
        m_func = func;
    }
	template<int>
    void Executor::setAction(bool (*func)())
    {
        m_obj = obj;
        m_func = func;
    }
    
    template<class T>
    void Executor<T>::setInterval(std::string & sentence)
    {
        parse(sentence);
    }
	template<int>
    void Executor::setInterval(std::string & sentence)
    {
        parse(sentence);
    }
    
    template<class T>
    void Executor<T>::setInterval(char * s)
    {
        std::string sentence(s);
        parse(sentence);
    }
	template<int>
    void Executor::setInterval(char * s)
    {
        std::string sentence(s);
        parse(sentence);
    }
    
    template<class T>
    void Executor<T>::parse(std::string & sentence)
    {
        // Call initialize method
        initialize();
        
        std::istringstream stream(sentence);
        std::string sub;
        
        IntervalType type = SEQUENCE_INTERVAL;
        typedef std::map<std::string, std::pair<int, IntervalType> > iterator;
        std::vector<std::pair<int, IntervalType> > integers;
        
        while (stream >> sub)
        {
            iterator::const_iterator it = m_humanTime.find(sub);
            if(it != m_humanTime.end())
            {
                std::pair<int, IntervalType> temp = it->second;
                integers.push_back(temp);
                
                if(temp.second > type)
                {
                    type = temp.second;
                }
            }
            else
            {
                bool isNumeric = true;
                for(int i = 0; i < sub.length(); i++)
                {
                    if(!std::isdigit(sub[i]))
                    {
                        isNumeric = false;
                        break;
                    }
                }
                
                if(isNumeric)
                {
                    int number = std::atoi(sub.c_str());
                    integers.push_back(std::make_pair(number, SEQUENCE_INTERVAL));
                }
            }
        }
        
        // Static Factory, is enough for this kind of class
        if(type == SEQUENCE_INTERVAL)
        {
            m_execute = new SequenceInterval(integers);
        }
        else if(type == TIME_INTERVAL)
        {
            m_execute = new TimeInterval(integers);
        }
    }
	template<int>
    void Executor::parse(std::string & sentence)
    {
        // Call initialize method
        initialize();
        
        std::istringstream stream(sentence);
        std::string sub;
        
        IntervalType type = SEQUENCE_INTERVAL;
        typedef std::map<std::string, std::pair<int, IntervalType> > iterator;
        std::vector<std::pair<int, IntervalType> > integers;
        
        while (stream >> sub)
        {
            iterator::const_iterator it = m_humanTime.find(sub);
            if(it != m_humanTime.end())
            {
                std::pair<int, IntervalType> temp = it->second;
                integers.push_back(temp);
                
                if(temp.second > type)
                {
                    type = temp.second;
                }
            }
            else
            {
                bool isNumeric = true;
                for(int i = 0; i < sub.length(); i++)
                {
                    if(!std::isdigit(sub[i]))
                    {
                        isNumeric = false;
                        break;
                    }
                }
                
                if(isNumeric)
                {
                    int number = std::atoi(sub.c_str());
                    integers.push_back(std::make_pair(number, SEQUENCE_INTERVAL));
                }
            }
        }
        
        // Static Factory, is enough for this kind of class
        if(type == SEQUENCE_INTERVAL)
        {
            m_execute = new SequenceInterval(integers);
        }
        else if(type == TIME_INTERVAL)
        {
            m_execute = new TimeInterval(integers);
        }
    }
    
    template<class T>
    bool Executor<T>::operator()()
    {
        if((*m_execute)())
        {
            return ((m_obj)->*(m_func))();
        }
        return false;
    }
	template<int>
    bool Executor::operator()()
    {
        if((*m_execute)())
        {
            return (*m_func)();
        }
        return false;
    }
    
    template<class T>
    void Executor<T>::initialize()
    {
        // mapping from human language to integers
        m_humanTime["once"] = std::make_pair(1, SEQUENCE_INTERVAL);
        m_humanTime["twice"] = std::make_pair(2, SEQUENCE_INTERVAL);
        m_humanTime["thrice"] = std::make_pair(3, SEQUENCE_INTERVAL);
        
        m_humanTime["one"] = std::make_pair(1, SEQUENCE_INTERVAL);
        m_humanTime["two"] = std::make_pair(2, SEQUENCE_INTERVAL);
        m_humanTime["three"] = std::make_pair(3, SEQUENCE_INTERVAL);
        m_humanTime["four"] = std::make_pair(4, SEQUENCE_INTERVAL);
        m_humanTime["five"] = std::make_pair(5, SEQUENCE_INTERVAL);
        m_humanTime["six"] = std::make_pair(6, SEQUENCE_INTERVAL);
        m_humanTime["seven"] = std::make_pair(7, SEQUENCE_INTERVAL);
        m_humanTime["eight"] = std::make_pair(8, SEQUENCE_INTERVAL);
        m_humanTime["nine"] = std::make_pair(9, SEQUENCE_INTERVAL);
        m_humanTime["ten"] = std::make_pair(10, SEQUENCE_INTERVAL);
        
        m_humanTime["day"] = std::make_pair(60 * 60 * 24, TIME_INTERVAL); // seconds in a day
        m_humanTime["week"] = std::make_pair(60 * 60 * 24 * 7, TIME_INTERVAL); // seconds in a week
        m_humanTime["month"] = std::make_pair(60 * 60 * 24 * 7 * 4, TIME_INTERVAL); // seconds in a month
        m_humanTime["year"] = std::make_pair(60 * 60 * 24 * 7 * 4 * 21, TIME_INTERVAL); // seconds in a year
    }
	template<int>
    void Executor::initialize()
    {
        // mapping from human language to integers
        m_humanTime["once"] = std::make_pair(1, SEQUENCE_INTERVAL);
        m_humanTime["twice"] = std::make_pair(2, SEQUENCE_INTERVAL);
        m_humanTime["thrice"] = std::make_pair(3, SEQUENCE_INTERVAL);
        
        m_humanTime["one"] = std::make_pair(1, SEQUENCE_INTERVAL);
        m_humanTime["two"] = std::make_pair(2, SEQUENCE_INTERVAL);
        m_humanTime["three"] = std::make_pair(3, SEQUENCE_INTERVAL);
        m_humanTime["four"] = std::make_pair(4, SEQUENCE_INTERVAL);
        m_humanTime["five"] = std::make_pair(5, SEQUENCE_INTERVAL);
        m_humanTime["six"] = std::make_pair(6, SEQUENCE_INTERVAL);
        m_humanTime["seven"] = std::make_pair(7, SEQUENCE_INTERVAL);
        m_humanTime["eight"] = std::make_pair(8, SEQUENCE_INTERVAL);
        m_humanTime["nine"] = std::make_pair(9, SEQUENCE_INTERVAL);
        m_humanTime["ten"] = std::make_pair(10, SEQUENCE_INTERVAL);
        
        m_humanTime["day"] = std::make_pair(60 * 60 * 24, TIME_INTERVAL); // seconds in a day
        m_humanTime["week"] = std::make_pair(60 * 60 * 24 * 7, TIME_INTERVAL); // seconds in a week
        m_humanTime["month"] = std::make_pair(60 * 60 * 24 * 7 * 4, TIME_INTERVAL); // seconds in a month
        m_humanTime["year"] = std::make_pair(60 * 60 * 24 * 7 * 4 * 21, TIME_INTERVAL); // seconds in a year
    }
}

#endif