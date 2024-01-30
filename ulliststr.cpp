#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}






// WRITE YOUR CODE HERE

//PUSH BACK
void ULListStr::push_back(const std::string& val)
{
   bool empty_or_end = false; 
   if(empty())
   {
    empty_or_end = true;
   }
   else if(tail_->last == ARRSIZE)
   {
    empty_or_end = true;
   }

   if(empty_or_end)
    {
    Item* newItem = new Item(); 
    newItem->val[0] = val;
    newItem->last++;
    
    if(empty())
    {
      head_ = newItem;
      tail_ = newItem;
    }
    else
    {
      newItem->prev = tail_;
      tail_->next = newItem;
      tail_ = newItem;
    } 
    }
  if(!empty_or_end)
  {
    tail_->val[tail_->last] = val; 
    tail_->last++;
  }
  size_++;
}

//PUSH FRONT
void ULListStr::push_front(const std::string& val)
{
  if (empty() || head_->first == 0)
  {
    Item* newItem = new Item();

    if (empty())
    {
      newItem->val[0] = val;
      newItem->first = 0;
      newItem->last = 1;
      head_ = tail_ = newItem;
    }
    else
    {
      newItem->next = head_;
      head_->prev = newItem;
      head_ = newItem;
      
      newItem->val[ARRSIZE - 1] = val;
      newItem->first = ARRSIZE - 1;
      newItem->last = ARRSIZE;
    }
  }
  else
  {
    head_->first--;
    head_->val[head_->first] = val;
  }

  size_++;
}

//POP BACK
void ULListStr::pop_back()
{
  if(empty())
  {
    return; 
  }
  tail_->last--;
  size_--; 

}

//POP FRONT
void ULListStr::pop_front()
{
  if (empty())
  {
    return;
  }

  if (size_ > 1 && head_->first != head_->last - 1)
  {
    head_->first++;
  }
  else
  {
    if (size_ == 1)
    {
      delete head_;
      head_ = tail_ = nullptr;
    }
    else
    {
      Item* original_head = head_;
      head_ = head_->next;
      if (head_ != nullptr)
      {
        head_->prev = nullptr;
      }
      delete original_head;
    }
  }
  size_--;
}

// BACK
std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last - 1];
}

//FRONT
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

//GETVALATLOC
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc > size_ || size_ < 0 || loc < 0)
  {
    return NULL;
  }

  Item* curr = head_;
  int remainingLoc = loc;

  while (curr != nullptr && remainingLoc >= (curr->last - curr->first))
  {
    remainingLoc -= (curr->last - curr->first);
    curr = curr->next;
  }

  if (curr == nullptr || remainingLoc < 0)
  {
    return NULL;
  }

  return &curr->val[curr->first + remainingLoc];

}







void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
