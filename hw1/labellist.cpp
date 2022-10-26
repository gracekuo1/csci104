#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(true);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
// Add any initializers here
 : node_(node), list_(list)
{

}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    if (this->node_ == rhs.node_)
        return true;
    return false;
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    return isValid();
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    // Add your code here
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    // Add your code here
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    if (this->isValid()){
       return node_->msg_;
    }
    else 
        throw std:: logic_error ("Invalid Message");
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg() 
{
   if (this->isValid()){
       return node_->msg_;
   }
   else 
        throw std:: logic_error ("Invalid Message");
}

// To be completed - must adhere to any requirements in the .h file
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList():
// Add any initializers here
heads_(), labels_()
{
    LabelType all = "all";
    labels_.push_back(all);
    heads_.push_back(nullptr);
    tails_.push_back(nullptr);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    MsgNode* current = heads_[0];
    while (current != nullptr){
        MsgNode* temp = current->next_[0];
        delete current;
        current = temp;
    }
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    MsgNode* current = heads_[0];
    while (current != nullptr){
        MsgNode* temp = current->next_[0];
        delete current;
        current = temp;
    }
    for (size_t i = 0; i < heads_.size()-1; i ++){
        labels_.pop_back();
        heads_.pop_back();
        tails_.pop_back();
    }
   
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    if(heads_[0] == nullptr)
        return true;
    return false;
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    MsgNode* new_node = new MsgNode (msg);
    new_node->labelled_[0] = true;
    new_node->next_[0] = nullptr;
    new_node->prev_[0] = nullptr;

    MsgNode* current = heads_[0];
    while (current != nullptr){
        current->labelled_.push_back(false);
        current->next_.push_back(nullptr);
        current->prev_.push_back(nullptr);
        current= current->next_[0];
    }

    if (heads_[0] == nullptr){
        heads_[0] = new_node;
        tails_[0] = new_node;
        //std::cout << "empty" << std::endl;
    }
    else {
        tails_[0]->next_[0] = new_node;
        new_node->prev_[0] = tails_[0];
        tails_[0] = new_node;
    }

    MsgToken new_token(new_node, this);
    return new_token;
} 


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    //std::cout << "remove" << std::endl;
    if (token.isValid()){
        for (size_t i = 0; i < labels_.size(); i ++){
            //node is the head
            if (token.isLabelMember(i)){
                //std::cout << token.node_->msg_ << std::endl;
                if (token.node_->prev_[i] == nullptr){ // changed(**)
                    //std::cout << "head" << std::endl;
                    heads_[i] = token.node_->next_[i];
                    if (token.node_->next_[i] != nullptr)
                        heads_[i]->prev_[i] = nullptr;
                }
                //node is the tail
                else if (token.node_->next_[i] == nullptr){ //changed(**)
                    //std::cout << "tail" << std::endl;
                    token.node_->next_[i] = nullptr;
                    tails_[i] = token.node_->prev_[i];
                    tails_[i]->next_[i] = nullptr;

                }
                //node is in the middle
                else {
                    //std::cout << "middle" << std::endl;
                    token.node_->prev_[i]->next_[i] = token.node_->next_[i];
                    token.node_->next_[i]->prev_[i] = token.node_->prev_[i];
                }
            }
        }
    }
    delete token.node_;
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    size_t index = findLabelIndex(label);
    bool labelNoExist = false;
    
    //label doesn't exist
    if(index == INVALID_LABEL){
        heads_.push_back(token.node_);
        tails_.push_back(token.node_);
        labels_.push_back(label);
        index  = findLabelIndex(label);
        //token.node_->next_[index] = nullptr;
        //token.node_->prev_[index] = nullptr;
        //std::cout << "label doens't exist yet " << labelNoExist << std::endl;
        labelNoExist = true;
        //token.node_->next_.push_back(nullptr); tOMATO
        //token.node_->prev_.push_back(nullptr); tOMATO

        //change lengths of next, labelled, and prev to accomodate approp index
        //***** you need to loop through with current and resize all the nodes/

        MsgNode* current = heads_[0];
        while (current != nullptr){
            //if (index >= current->labelled_.size()){
                //std::cout << "change to index+1 "<< std::endl;
            current->labelled_.resize(index+1, false);
            current->next_.resize(index+1, NULL);
            current->prev_.resize(index+1, NULL);
            //}
            current = current->next_[0];
        }
    }
    //std::cout << "index " << index << std::endl;

    //set labelled to true
    token.node_->labelled_[index] = true;
    
    //label does exist but no messages
    if (heads_[index] == nullptr && !labelNoExist){
        //std::cout << "label alr exists "<< std::endl;
        heads_[index] = token.node_;
        tails_[index] = token.node_;
        token.node_->next_[index] = nullptr;
        token.node_->prev_[index] = nullptr;
    }
    //label does exist and there are already messages
    else if (!labelNoExist){
        //std::cout << "label exists and there are messages "<< std::endl;
        bool isHead = true;
        bool isTail = true; 

        MsgNode* current = token.node_;
        while(current->prev_[0] != nullptr){
            current = current->prev_[0];
            //std::cout << current->prev_[0] << std::endl;
            if (current->labelled_[index] == true){
                isHead = false;
                break;
            }
        }
        //std::cout << "head" << isHead << std::endl;

        current = token.node_;
        //std::cout << current->next_[0] << std::endl;
        while(current->next_[0] != nullptr){
            current = current->next_[0];
            //std::cout << "in " << current->msg_ << std::endl;
            if (current->labelled_[index] == true){
                isTail = false;
                break;
            }
        }
        //std::cout << "tail" << isTail << std::endl;

        //std::cout << isHead << " " << isTail << std::endl;
        //if its the head
        if (isHead){
            //std::cout <<"ishead" << std::endl;
            heads_[index]->prev_[index] = token.node_;
            token.node_->prev_[index] = nullptr;
            token.node_->next_[index] = heads_[index];
            heads_[index] = token.node_;
            //std::cout << token.node_<< std::endl;
            //std::cout << token.node_->next_[index] << std::endl;

        }
        //if its the tail
        else if (isTail){
            //std::cout <<"istail" << std::endl;
            tails_[index]->next_[index] = token.node_;
            token.node_->prev_[index] = tails_[index];
            token.node_->next_[index] = nullptr;
            tails_[index] = token.node_;
        }
        //if it's in the middle
        else {
            current = token.node_;
            while(current->prev_[0] != nullptr){
                current = current->prev_[0];
                if (current->labelled_[index] == true){
                    token.node_->next_[index] = current->next_[index];
                    if (current->next_[index] != nullptr)
                        current->next_[index]->prev_[index] = token.node_;
                    current->next_[index] = token.node_;
                    token.node_->prev_[index] = current;
                    break;
                }
            }
        }
    }
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }

    size_t i = getLabelIndex(label);
    
    if (label != labels_[0] && token.node_->labelled_[i] == true){
        //node is the head
        if (heads_[i] == token.node_){
            heads_[i] = token.node_->next_[i];
            if (token.node_->next_[i] != nullptr)
                heads_[i]->prev_[i] = nullptr;
            //token.node_->prev_[i] = nullptr;
            //heads_[i] = token.node_->next_[i];
        }
        //node is the tail
        else if (tails_[i] == token.node_){
            token.node_->next_[i] = nullptr;
            tails_[i] = token.node_->prev_[i];
            tails_[i]->next_[i] = nullptr;
            //token.node_->next_[i] = nullptr;
            //tails_[i] = token.node_->prev_[i];
        }
        //node is in the middle
        else {
            token.node_->prev_[i]->next_[i] = token.node_->next_[i];
            token.node_->next_[i]->prev_[i] = token.node_->prev_[i];
        }
    }

}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{
    size_t label_i = this->getLabelIndex(label);
    MsgNode* current = this->heads_[label_i];
    //std::cout << "current " << current << std::endl;

    //if (current == nullptr)
    //    return end();

    size_t i = 0;
    while (current != nullptr){
        if(i == index)
        {
            //std::cout << "found " << current->msg_ << std::endl;
            return MsgToken(current, this);
        }
        current = current->next_[label_i];
        i++;
    }
    return end();

    //std::cout << current->msg_ << std::endl;

    /*for (size_t i = 0; i < index; i ++){
        if(current != nullptr){
            std::cout << "in " << current->next_[label_i]->msg_ << std::endl;
            current = current->next_[label_i];
        }
        else 
            return end_;
    }
    MsgToken new_token(current, this);
    return new_token;
    */
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    for (size_t i = 0; i < labels_.size(); i++){
        if (labels_[i] == label)
            return i;
    }
    return INVALID_LABEL;
}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


