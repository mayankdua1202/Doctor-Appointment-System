class singleLL
{
    node *head;
    public:
    singleLL()
    {
        head = NULL;
    }

    node *insertNode(int);
    int  countPatients();
    void printList();
    void arrangeList();
    bool isEmpty()
    {
        if(head==NULL)
            return true;
        return false;
    }
    bool isFull()
    {
        int ones = 0;
        for(int i=0;i<MAX_PATIENTS;i++)
        {
            if(patients[i] == 1)
                ones++;
        }
        if(ones == MAX_PATIENTS)
            return true;
        return false;
    }

    int findSmallestAppNoPatient();
    node * DeleteFromPatientPosition(int);

};


node* singleLL :: insertNode(int pos)
{
    node* newNode = getNewPatient();

    if(pos == 1)
    {
        newNode->next = head;
        head = newNode;
        return head;
    }

    node* temp = head;
    for(int i=0; i<pos-2; i++)
    {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    return head;
}

int singleLL::countPatients()
{
    node* temp = head;
    int Count = 0;
    while(temp){
        Count++;
        temp = temp->next;
    }
    return Count;
}

void singleLL :: printList()
{
    cout<<"PATIENTS LIST : ";
    node* temp = head;
    if(!head)
        cout<<""<<endl;

    while(temp){
        cout<<temp->patientName<<"("<<temp->appId<<") ";
        temp = temp->next;
    }
    cout<<endl;
}

node* Merge(node* a, node* b)
{
    node* result = NULL;
    if(!a)
        return b;
    if(!b)
        return a;

    if(a->appId <= b->appId)
    {
        result = a;
        result->next = Merge(a->next, b);
    }
    else
    {
        result = b;
        result->next = Merge(a, b->next);
    }
    return result;
}

node* MergeSort(node* head)
{
    if(!head || !head->next)
        return head;

    node *slow = head, *fast = head->next;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    fast = slow->next;
    slow->next = NULL;

    return Merge(MergeSort(head), MergeSort(fast));
}

void singleLL::arrangeList()
{
    head = MergeSort(head);
}

int singleLL::findSmallestAppNoPatient()
{
    node *temp = head;
    int pos = 0;
    int patId = INT_MAX;

    int result = 0;

    while(temp!=NULL)
    {
        pos++;
        if(patId > temp->appId)
        {
            patId = temp->appId;
            result = pos;
        }
        temp = temp->next;
    }
    if(patId>=0 && patId<MAX_PATIENTS)
        patients[patId] = 0;    // We are assuming that this function will be called, only when we have to remove a patient from the list

    return result;
}

node* singleLL :: DeleteFromPatientPosition(int pos)
{
    if(head==NULL)
    {
        cout<<"List is Empty!"<<endl;
        return head;
    }
    node* temp1 = head;
    if(pos == 1)
    {
        head = temp1->next;
        return temp1;
    }

    for(int i=0; i<pos-2; i++)
    {
        temp1 = temp1->next;
    }

    node* temp2 = temp1->next;
    temp1->next  = temp2->next;
    return temp2;
}
