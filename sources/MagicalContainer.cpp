#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

    void MagicalContainer::addElement(int element)
    {
        this->originalContainer.push_back(element);
        updateIterators(element, 1, 0);
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = std::find(originalContainer.begin(), originalContainer.end(), element);

        if (it != originalContainer.end())
        {
            originalContainer.erase(it);
            std::cout << "Element " << element << " removed from the vector." << std::endl;
        }
        else
        {
            throw runtime_error("not such element in the vector!");
        }   

        updateIterators(element, 0, 1);
    }

    bool MagicalContainer::isPrime(int element)
    {
        if (element <= 1) {
            return false;
        }

        for (int i = 2; i * i <= element; ++i) {
            if (element % i == 0) {
                return false;
            }
        }
        return true;
    }

    int MagicalContainer::size()
    {
        return this->originalContainer.size();
    }

    void MagicalContainer::updateIterators(int element, int insertIt, int deleteIt)
    {
        updateAscending(element,insertIt, deleteIt);
        updateCross(element, insertIt, deleteIt);
        updatePrime(element,insertIt, deleteIt);
    }

    void MagicalContainer::updateAscending(int element, int insertIt, int deleteIt)
    {
        if (insertIt)
        {
            if (!AscendingContainer.size())
            {
                AscendingContainer.push_back(element);
            }
            else
            {
                int isEntered = 0;
                for (size_t i = 0; i < AscendingContainer.size(); i++)
                {
                    if (AscendingContainer[i] > element)
                    {
                        auto insertPos = AscendingContainer.begin()  + static_cast<std::vector<int>::difference_type>(i);
                        AscendingContainer.insert(insertPos, element);
                        i = AscendingContainer.size() + 1;
                        isEntered = 1;
                        break;
                    }
                }
                if (!isEntered)
                {
                    AscendingContainer.push_back(element);
                }
                
            }
        }
        else
        {
            auto it = std::find(AscendingContainer.begin(), AscendingContainer.end(), element);

            if (it != AscendingContainer.end())
            {
                AscendingContainer.erase(it);
                std::cout << "Element " << element << " removed from the vector." << std::endl;
            }
            else
            {
                std::cout << "Element " << element << " not found in the vector." << std::endl;
            }   
        }
    }

    void MagicalContainer::updateCross(int element, int insertIt, int deleteIt)
    {
        if (insertIt)
        {
            if (!SideCrossContainer.size())
            {
                SideCrossContainer.push_back(element);
            }
            else
            {
                int isEntered = 0;
                for (size_t i = 0; i < SideCrossContainer.size(); i++)
                {
                    if (SideCrossContainer[i] > element)
                    {
                        auto insertPos = SideCrossContainer.begin()  + static_cast<std::vector<int>::difference_type>(i);
                        SideCrossContainer.insert(insertPos, element);
                        i = SideCrossContainer.size() + 1;
                        isEntered = 1;
                        break;
                    }
                }
                if (!isEntered)
                {
                    SideCrossContainer.push_back(element);
                }
            }
        }
        else
        {
            auto it = std::find(SideCrossContainer.begin(), SideCrossContainer.end(), element);

            if (it != SideCrossContainer.end())
            {
                SideCrossContainer.erase(it);
                std::cout << "Element " << element << " removed from the vector." << std::endl;
            }
            else
            {
                std::cout << "Element " << element << " not found in the vector." << std::endl;
            }   
        }
        std::sort(SideCrossContainer.begin(), SideCrossContainer.end());
        std::vector<int> rearranged;
        auto startOf = SideCrossContainer.begin();
        auto endOf = SideCrossContainer.end() - 1;

        while(startOf <= endOf)
        {
            rearranged.push_back(*startOf);

            if(startOf != endOf)
            {
                rearranged.push_back(*endOf);
            }
            ++startOf;
            --endOf;    
        }
        this->SideCrossContainer = rearranged;
    }

    void MagicalContainer::updatePrime(int element,int insertIt, int deleteIt)
    {
        if (insertIt)
        {
            if (isPrime(element))
            {
                this->PrimeContainer.push_back(element);
            }
        }
        else
        {
            auto it = std::find(PrimeContainer.begin(), PrimeContainer.end(), element);

            if (it != PrimeContainer.end())
            {
                PrimeContainer.erase(it);
                std::cout << "Element " << element << " removed from the vector." << std::endl;
            }
            else
            {
                std::cout << "Element " << element << " not found in the vector." << std::endl;
            }   
        }
    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& mgc)
    : mgc(&mgc)
    {
        this->curr = this->mgc->AscendingContainer.begin();
    }

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : mgc(other.mgc)
    {
        this->curr = this->mgc->AscendingContainer.begin();
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
    {
        if(this->curr == this->mgc->AscendingContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        this->curr++;
        return *this;
    }

    bool MagicalContainer::AscendingIterator::operator==(AscendingIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        if(this->curr == other.curr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool MagicalContainer::AscendingIterator::operator!=(AscendingIterator& other)
    {
        return !(this->operator==(other));
    }

    bool MagicalContainer::AscendingIterator::operator<(AscendingIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr < other.curr);
    } 

    bool MagicalContainer::AscendingIterator::operator>(AscendingIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr > other.curr);
    }

    int MagicalContainer::AscendingIterator::operator*()
    {
        if(this->curr == this->mgc->AscendingContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        return *this->curr;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw runtime_error("Iterators are not of the same type");
        }

        this->mgc = other.mgc;
        this->curr = other.curr;

        return *this;
    }


    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        AscendingIterator begPo(*this);
        return begPo;
    }   

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
    {
        AscendingIterator endPo(*this);
        endPo.curr = this->mgc->AscendingContainer.end();
        return endPo;
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& mgc)
    : mgc (&mgc)
    {
        curr = mgc.SideCrossContainer.begin();
    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : mgc(other.mgc)
    {
        this->curr = this->mgc->SideCrossContainer.begin();
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
    {
        if(this->curr == this->mgc->SideCrossContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        this->curr++;
        return *this;
    }

    bool MagicalContainer::SideCrossIterator::operator==(SideCrossIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        if(this->curr == other.curr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool MagicalContainer::SideCrossIterator::operator!=(SideCrossIterator& other)
    {
        return !(this->operator==(other));
    }

    bool MagicalContainer::SideCrossIterator::operator<(SideCrossIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr < other.curr);
    } 

    bool MagicalContainer::SideCrossIterator::operator>(SideCrossIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr > other.curr);
    }

    int MagicalContainer::SideCrossIterator::operator*()
    {
        if(this->curr == this->mgc->SideCrossContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        return *this->curr;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw runtime_error("Iterators are not of the same type");
        }

        this->mgc = other.mgc;
        this->curr = other.curr;

        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        SideCrossIterator begPo(*this);
        return begPo;
    }   

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        SideCrossIterator endPo(*this);
        endPo.curr = this->mgc->SideCrossContainer.end();
        return endPo;
    }

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& mgc)
    : mgc(&mgc)
    {
        curr = mgc.PrimeContainer.begin();
        
    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : mgc(other.mgc)
    {
        this->curr = this->mgc->PrimeContainer.begin();
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
    {
        if(this->curr == this->mgc->PrimeContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        this->curr++;
        return *this;
    }

    bool MagicalContainer::PrimeIterator::operator==(PrimeIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        if(this->curr == other.curr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool MagicalContainer::PrimeIterator::operator!=(PrimeIterator& other)
    {
        return !(this->operator==(other));
    }

    bool MagicalContainer::PrimeIterator::operator<(PrimeIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr < other.curr);
    } 

    bool MagicalContainer::PrimeIterator::operator>(PrimeIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw invalid_argument("Iterators are not of the same type");
        }

        return (this->curr > other.curr);
    }

    int MagicalContainer::PrimeIterator::operator*()
    {
        if(this->curr == this->mgc->PrimeContainer.end())
        {
            throw runtime_error("Iterator is already at the end of the vector!");
        }
        return *this->curr;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
    {
        if(this->mgc != other.mgc)
        {
            throw runtime_error("Iterators are not of the same type");
        }

        this->mgc = other.mgc;
        this->curr = other.curr;

        return *this;
    }


    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        PrimeIterator begPo(*this);
        return begPo;
    }   

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        PrimeIterator endPo(*this);
        endPo.curr = this->mgc->PrimeContainer.end();
        return endPo;
    }