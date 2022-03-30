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

{
    //sets node_ and list_ to the given parameters
    this->node_ = node;
    this->list_ = list;
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    //compares whether rhs and lhs tokens are the same
    if(node_ == rhs.node_){
        return true;
    }
    else{
        return false;
    }
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    //checks whether the token itself is valid and uses itself as a bool
    if(isValid()){
        return true;
    }
    else return false;
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
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
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    //returns the message from a token
    if(this->isValid()){
        return this->node_->msg_;
    }
    else throw std::logic_error("Invalid message");
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg()
{
    //non const version of returning a message from a token
    if(this->isValid()){
        return this->node_->msg_;
    }
    else throw std::logic_error("Invalid message");
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
LabelList::LabelList()
// Add any initializers here

{
    heads_.push_back(NULL);
    tails_.push_back(NULL);
    labels_.push_back("all");
    
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    /* Using clear to deallocate all memory, since clear deletes every node*/
    clear();
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    //deletes all nodes
    while(!empty()){
        remove(find(0, "all"));
    }
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    //a list is empty when the all label head points to nothing
    if(heads_[0] == NULL) return true;
    else return false;
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
    MsgNode* newNode = new MsgNode(msg);
    if(heads_[0] == NULL){
        heads_[0] = newNode;
        tails_[0] = newNode;
    }
    else{
        //adding a new msgnode to the back
        newNode->prev_[0] = tails_[0];
        tails_[0]->next_[0] = newNode;
        tails_[0] = newNode;
        size_t missingLabels = labels_.size();
        size_t i = 1;
        //checks whether there are labels other than all
        while(i != missingLabels && missingLabels > 0){
            newNode->labelled_.push_back(false);
            newNode->prev_.push_back(NULL);
            newNode->next_.push_back(NULL);
            ++i;
        }
    }
    
    MsgToken newToken = MsgToken(newNode, this);
    return newToken;
}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    if(!empty()){
        if(token.isValid()){
            //removing all labels but "all" from a node
            for(unsigned i = 1; i < labels_.size(); ++i){
                if(token.node_->labelled_[i] == true){
                    unlabel(token, labels_[i]);
                }
            }
            //removes the node from "all" label, then deallocates its memory
            MsgNode* temp = heads_[0];
            while(temp != token.node_){
                temp = temp->next_[0];
            }
            if(temp == tails_[0]){
                if(temp != heads_[0]){
                    temp->prev_[0]->next_[0] = NULL;
                    tails_[0] = temp->prev_[0];
                }
                else{
                    heads_[0] = NULL;
                    tails_[0] = NULL;
                }
            }
            else if(temp->prev_[0] == NULL){
                temp->next_[0]->prev_[0] = NULL;
                heads_[0] = temp->next_[0];
            }
            else{
                temp->next_[0]->prev_[0] = temp->prev_[0];
                temp->prev_[0]->next_[0] = temp->next_[0];
            }
            delete token.node_;
        }
        else{
            return;
        }
    }
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    else{
        //shouldn't be labelling all
        if(label == "all") return;
        
        size_t index = findLabelIndex(label);
        //if not a label, add the label and pushback labbeled for every node
        if(index == INVALID_LABEL){
            labels_.push_back(label);
            heads_.push_back(token.node_);
            tails_.push_back(token.node_);
            MsgNode* temp = heads_[0];
            while(temp != NULL){
                if(temp == token.node_) temp->labelled_.push_back(true);
                else temp->labelled_.push_back(false);
                temp->next_.push_back(NULL);
                temp->prev_.push_back(NULL);
                temp = temp->next_[0];
            }
        }
        else{
            //adding to an empty existing label
            if(heads_[index] == NULL){
                heads_[index] = token.node_;
                tails_[index] = token.node_;
            }
            else{
                //adding to an occupied existing label
                MsgNode* temp = heads_[0];
                //finding how many come before the given node with such label
                int count = 0;
                while(temp != token.node_){
                    if(temp->labelled_[index] == true) ++count;
                    temp = temp->next_[0];
                }
                //checks if the node is going to be add at the front
                if(!count){
                    token.node_->next_[index] = heads_[index];
                    heads_[index]->prev_[index] = token.node_;
                    heads_[index] = token.node_;
                }
                else{
                    temp = heads_[index];
                    for(int i = 1; i < count; ++i){
                        temp = temp->next_[index];
                    }
                    //checks if the node prior is at tail
                    if(tails_[index] == temp){
                        token.node_->prev_[index] = temp;
                        temp->next_[index] = token.node_;
                        tails_[index] = token.node_;
                    }
                    else{
                        token.node_->next_[index] = temp->next_[index];
                        token.node_->prev_[index] = temp;
                        temp->next_[index] = token.node_;
                    }
                }
            }
            token.node_->labelled_[index] = true;
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
    
    if(label != "all"){
        size_t index = findLabelIndex(label);
        //checks if the label is non-existent or a node that has no such label
        if(index == INVALID_LABEL) throw std::out_of_range("non-existent label is provided");
        if(token.node_->labelled_[index] == false) return;
        
        MsgNode* temp = heads_[index];
        while(temp != token.node_){
            temp = temp->next_[index];
        }
        //removing a node if at the end
        if(tails_[index] == temp){
            //checks if the node is single in the list
            if(heads_[index] != temp){
                temp->prev_[index]->next_[index] = NULL;
                tails_[index] = temp->prev_[index];
            }
            else{
                heads_[index] = NULL;
                tails_[index] = NULL;
            }
        }
        //removing a node if at the front
        else if(temp->prev_[index] == NULL){
            temp->next_[index]->prev_[index] = NULL;
            heads_[index] = temp->next_[index];
        }
        //removing a node in between two nodes
        else{
            temp->next_[index]->prev_[index] = temp->prev_[index];
            temp->prev_[index]->next_[index] = temp->next_[index];
        }
        temp->labelled_[index] = false;
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
    // See if the label exists using index, will throw if not
    size_t check = this->getLabelIndex(label);
    MsgNode* temp = heads_[check];
    size_t count = 0;
    while(temp != NULL){
        if(count == index){
            return MsgToken(temp, this);
        }
        temp = temp->next_[check];
        ++count;
    }
    return end();
    
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
    /* if the label exists then there must exist an index within the labels vector
       if not then return it is an invalid label
    */
    size_t retval = 0;
    for(unsigned int i = 0; i < labels_.size(); ++i){
        if(labels_[i] == label){
            retval = i;
            return retval;
        }
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
