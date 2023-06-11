#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

void MagicalContainer::addElement(int element)
{
    // Add the element to the original container
    this->originalContainer.push_back(element);
    // Update the iterators
    updateIterators(element, 1, 0);
}

void MagicalContainer::removeElement(int element)
{
    // Find the element in the original container
    auto it = std::find(originalContainer.begin(), originalContainer.end(), element);

    if (it != originalContainer.end())
    {
        // Remove the element from the original container
        originalContainer.erase(it);
        std::cout << "Element " << element << " removed from the vector." << std::endl;
    }
    else
    {
        throw runtime_error("No such element in the vector!");
    }

    // Update the iterators
    updateIterators(element, 0, 1);
}

bool MagicalContainer::isPrime(int element)
{
    // Check if the element is prime
    if (element <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= element; ++i)
    {
        if (element % i == 0)
        {
            return false;
        }
    }
    return true;
}

int MagicalContainer::size()
{
    // Return the size of the original container
    return this->originalContainer.size();
}

void MagicalContainer::updateIterators(int element, int insertIt, int deleteIt)
{
    // Update the ascending iterator
    updateAscending(element, insertIt, deleteIt);
    // Update the side cross iterator
    updateCross(element, insertIt, deleteIt);
    // Update the prime iterator
    updatePrime(element, insertIt, deleteIt);
}

void MagicalContainer::updateAscending(int element, int insertIt, int deleteIt)
{
    if (insertIt)
    {
        if (!AscendingContainer.size())
        {
            // If the ascending container is empty, add the element directly
            AscendingContainer.push_back(element);
        }
        else
        {
            int isEntered = 0;
            // Find the correct position to insert the element in the ascending container
            for (size_t i = 0; i < AscendingContainer.size(); i++)
            {
                if (AscendingContainer[i] > element)
                {
                    auto insertPos = AscendingContainer.begin() + static_cast<std::vector<int>::difference_type>(i);
                    AscendingContainer.insert(insertPos, element);
                    // Exit the loop after inserting the element
                    i = AscendingContainer.size() + 1;
                    isEntered = 1;
                    break;
                }
            }
            if (!isEntered)
            {
                // If the element is greater than all existing elements, add it at the end
                AscendingContainer.push_back(element);
            }
        }
    }
    else
    {
        // Remove the element from the ascending container
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
            // If the side cross container is empty, add the element directly
            SideCrossContainer.push_back(element);
        }
        else
        {
            int isEntered = 0;
            // Find the correct position to insert the element in the side cross container
            for (size_t i = 0; i < SideCrossContainer.size(); i++)
            {
                if (SideCrossContainer[i] > element)
                {
                    auto insertPos = SideCrossContainer.begin() + static_cast<std::vector<int>::difference_type>(i);
                    SideCrossContainer.insert(insertPos, element);
                    // Exit the loop after inserting the element
                    i = SideCrossContainer.size() + 1;
                    isEntered = 1;
                    break;
                }
            }
            if (!isEntered)
            {
                // If the element is greater than all existing elements, add it at the end
                SideCrossContainer.push_back(element);
            }
        }
    }
    else
    {
        // Remove the element from the side cross container
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

    // Sort the side cross container in ascending order
    std::sort(SideCrossContainer.begin(), SideCrossContainer.end());

    // Rearrange the side cross container
    std::vector<int> rearranged;
    auto startOf = SideCrossContainer.begin();
    auto endOf = SideCrossContainer.end() - 1;

    while (startOf <= endOf)
    {
        rearranged.push_back(*startOf);

        if (startOf != endOf)
        {
            rearranged.push_back(*endOf);
        }
        ++startOf;
        --endOf;
    }
    this->SideCrossContainer = rearranged;
}

void MagicalContainer::updatePrime(int element, int insertIt, int deleteIt)
{
    if (insertIt)
    {
        // If the element is prime, add it to the prime container
        if (isPrime(element))
        {
            this->PrimeContainer.push_back(element);
        }
    }
    else
    {
        // Remove the element from the prime container
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
    // Initialize the iterator at the beginning of the ascending container
    this->curr = this->mgc->AscendingContainer.begin();
}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other)
    : mgc(other.mgc)
{
    // Initialize the iterator at the beginning of the ascending container
    this->curr = this->mgc->AscendingContainer.begin();
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++()
{
    // Move the iterator to the next element in the ascending container
    if (this->curr == this->mgc->AscendingContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    this->curr++;
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(AscendingIterator& other)
{
    // Check if two iterators are equal
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    if (this->curr == other.curr)
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
    // Check if two iterators are not equal
    return !(this->operator==(other));
}

bool MagicalContainer::AscendingIterator::operator<(AscendingIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr < other.curr);
}

bool MagicalContainer::AscendingIterator::operator>(AscendingIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr > other.curr);
}

int MagicalContainer::AscendingIterator::operator*()
{
    // Dereference the iterator to get the current element
    if (this->curr == this->mgc->AscendingContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    return *this->curr;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other)
{
    // Assign one iterator to another
    if (this->mgc != other.mgc)
    {
        throw runtime_error("Iterators are not of the same type");
    }

    this->mgc = other.mgc;
    this->curr = other.curr;

    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    // Return an iterator at the beginning of the ascending container
    AscendingIterator begPo(*this);
    return begPo;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    // Return an iterator at the end of the ascending container
    AscendingIterator endPo(*this);
    endPo.curr = this->mgc->AscendingContainer.end();
    return endPo;
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& mgc)
    : mgc(&mgc)
{
    // Initialize the iterator at the beginning of the side cross container
    curr = mgc.SideCrossContainer.begin();
}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other)
    : mgc(other.mgc)
{
    // Initialize the iterator at the beginning of the side cross container
    this->curr = this->mgc->SideCrossContainer.begin();
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    // Move the iterator to the next element in the side cross container
    if (this->curr == this->mgc->SideCrossContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    this->curr++;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(SideCrossIterator& other)
{
    // Check if two iterators are equal
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    if (this->curr == other.curr)
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
    // Check if two iterators are not equal
    return !(this->operator==(other));
}

bool MagicalContainer::SideCrossIterator::operator<(SideCrossIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr < other.curr);
}

bool MagicalContainer::SideCrossIterator::operator>(SideCrossIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr > other.curr);
}

int MagicalContainer::SideCrossIterator::operator*()
{
    // Dereference the iterator to get the current element
    if (this->curr == this->mgc->SideCrossContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    return *this->curr;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
{
    // Assign one iterator to another
    if (this->mgc != other.mgc)
    {
        throw runtime_error("Iterators are not of the same type");
    }

    this->mgc = other.mgc;
    this->curr = other.curr;

    return *this;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    // Return an iterator at the beginning of the side cross container
    SideCrossIterator begPo(*this);
    return begPo;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    // Return an iterator at the end of the side cross container
    SideCrossIterator endPo(*this);
    endPo.curr = this->mgc->SideCrossContainer.end();
    return endPo;
}

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& mgc)
    : mgc(&mgc)
{
    // Initialize the iterator at the beginning of the prime container
    curr = mgc.PrimeContainer.begin();
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other)
    : mgc(other.mgc)
{
    // Initialize the iterator at the beginning of the prime container
    this->curr = this->mgc->PrimeContainer.begin();
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++()
{
    // Move the iterator to the next element in the prime container
    if (this->curr == this->mgc->PrimeContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    this->curr++;
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(PrimeIterator& other)
{
    // Check if two iterators are equal
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    if (this->curr == other.curr)
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
    // Check if two iterators are not equal
    return !(this->operator==(other));
}

bool MagicalContainer::PrimeIterator::operator<(PrimeIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr < other.curr);
}

bool MagicalContainer::PrimeIterator::operator>(PrimeIterator& other)
{
    // Compare two iterators
    if (this->mgc != other.mgc)
    {
        throw invalid_argument("Iterators are not of the same type");
    }

    return (this->curr > other.curr);
}

int MagicalContainer::PrimeIterator::operator*()
{
    // Dereference the iterator to get the current element
    if (this->curr == this->mgc->PrimeContainer.end())
    {
        throw runtime_error("Iterator is already at the end of the vector!");
    }
    return *this->curr;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other)
{
    // Assign one iterator to another
    if (this->mgc != other.mgc)
    {
        throw runtime_error("Iterators are not of the same type");
    }

    this->mgc = other.mgc;
    this->curr = other.curr;

    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    // Return an iterator at the beginning of the prime container
    PrimeIterator begPo(*this);
    return begPo;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    // Return an iterator at the end of the prime container
    PrimeIterator endPo(*this);
    endPo.curr = this->mgc->PrimeContainer.end();
    return endPo;
}

