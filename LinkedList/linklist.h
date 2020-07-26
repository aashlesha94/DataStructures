struct LinkNode {
    int data;
    LinkNode* next;
public:
    LinkNode(int data, LinkNode* next) : data(data), next(next) {}
};

class LinkList {
public:
    LinkNode* head = nullptr;
    LinkList(int data) {
        this->head = create_node(data);
    }
    LinkList(std::vector<int> vec) {
        if (!vec.size()) {
            this->head = nullptr;
            return;
        }
        this->head = create_node(vec[0]);
        auto temp = this->head;
        for (int i = 1; i < vec.size(); i++) {
            temp->next = create_node(vec[i]);
            temp = temp->next;
        }
    }
    LinkNode* create_node(int data) {
        return(new LinkNode(data, nullptr));
    }
    void add_after(LinkNode* node, int data) {
        if (!node) return;
        auto newNode = create_node(data);
        auto temp = node->next;
        node->next = newNode;
        newNode->next = temp;
        return;
    }
    int size() {
        auto temp = head;
        int idx = 0;
        while (temp) {
            temp = temp->next;
            idx++;
        }
        return idx;
    }
    LinkNode* getLastNode() {
        if (!this->head) return nullptr;
        LinkNode* temp = this->head;
        while (temp->next) {
            temp = temp->next;
        }
        return temp;
    }
    void add_last(int data) {
        auto last = getLastNode();
        add_after(last, data);
        return;
    }

    LinkNode* find(int key) {
        auto temp = head;
        while (temp) {
            if (temp->data == key)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void delete_data (int data) {
        auto pres = head;
        LinkNode* prev = nullptr;
        while (pres) {
            if (pres->data == data) {
                if (prev) {
                    prev->next = pres->next;
                    return;
                }
                else {
                    head = pres->next;
                    return;
                }
            }
            else {
                prev = pres;
pres = pres->next;
            }
        }
        return;
    }
    void traverse_and_print() {
        auto temp = head;
        while (temp) {
            std::cout << "Data :" << temp->data << std::endl;
            temp = temp->next;
        }
        return;
    }

    void reverse() {
        LinkNode* next = head;
        LinkNode* prev = nullptr;
        while (next) {
            auto next_next = next->next;
            next->next = prev;
            prev = next;
            next = next_next;
        }
        this->head = prev;
        return;
    }
    LinkNode* find_cycle() {
        auto slow_ptr = head;
        auto fast_ptr = head;
        while (slow_ptr && fast_ptr) {
            slow_ptr = slow_ptr->next;
            if (fast_ptr->next) {
                fast_ptr = fast_ptr->next->next;
            }
            else {
                return nullptr;
            }
            if (slow_ptr == fast_ptr) {
                slow_ptr = head;
                while (slow_ptr != fast_ptr) {
                    slow_ptr = slow_ptr->next;
                    fast_ptr = fast_ptr->next;
                }
                return slow_ptr;
            }
        }
        return nullptr;
    }

    static LinkList* merge_sorted_ll(LinkList* list1, LinkList* list2) {
        LinkList* outputList = nullptr;
        LinkNode* origHead = nullptr;
        LinkNode* otherHead = nullptr;
        LinkNode* prev = nullptr;
        if (!list1->head) return list2;
        else if (!list2->head) return list1;

        if (list1->head->data <= list2->head->data) {
            outputList = list1;
            origHead = list1->head->next;
            otherHead = list2->head;
            prev = list1->head;
        }
        else {
            outputList = list2;
            origHead = list2->head->next;
            otherHead = list1->head;
            prev = list2->head;
        }
        while (origHead && otherHead) {
            if (origHead->data > otherHead->data) {
                prev->next = otherHead;
                while (otherHead->next && origHead->data > otherHead->next->data) {
                    otherHead = otherHead->next;
                }
                auto temp = otherHead;
                otherHead = otherHead->next;
                temp->next = origHead;
            }
            prev = origHead;
            origHead = origHead->next;
        }
        if (otherHead) {
            prev->next = otherHead;
        }
        return outputList;
    }

    static std::vector<int> greaterNext(LinkList* ll) {
        auto head = ll->head;
        int size = ll->size();
        struct el_idx {
            int element;
            int idx;
            el_idx(int element, int idx) : element(element), idx(idx) { }
        };
        std::vector<int> output(size);
        std::stack<el_idx> element_stk;
        std::stack<el_idx> backup;
        int idx = 0;
        while (head) {
            if (!element_stk.empty()) {
                if (head->data > element_stk.top().element) {
                    while (!element_stk.empty() && head->data > element_stk.top().element) {
                        output[element_stk.top().idx] = head->data;
                        element_stk.pop();
                    }
                } else if (head->data < element_stk.top().element) {
                    while (head->data >= element_stk.top().element) {
                        backup.push(element_stk.top());
                        element_stk.pop();
                    }
                }
            }
            element_stk.push(el_idx(head->data, idx));
            while (!backup.empty()) {
                element_stk.push(backup.top());
                backup.pop();
            }
            head = head->next;
            idx++;
        }
        while (!element_stk.empty()) {
            output[element_stk.top().idx] = 0;
            element_stk.pop();
        }
        return output;
        
    }
};
