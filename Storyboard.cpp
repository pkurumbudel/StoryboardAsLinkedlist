/******************************************************************************

I decided to use array list for tags, and Linked list for storing the Storyboards.
This implementation is giving segmentation fault, did not have time to debug the code.
So, submitting as it is.

*******************************************************************************/

#include <iostream>
#include <iostream> 
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>

using namespace std;

class Note
{
public:
    string getTitle()
    {
        return title;
    }
    
    string getText()
    {
        return text;
    }
    
    std::vector<string> getTags()
    {
        return tags;
    }
    
    void setTitle(string name)
    {
        title = name;
    }
    
    void setText(string newText)
    {
        text = newText;
    }
    
    void insertTags(string tag)
    {
        tags.push_back(tag);
    }
    
    class Note* getNext()
    {
        return next;
    }
    
    void setNext(class Note* newNode)
    {
        next = newNode;
    }
    
private:
	string title;
    string text;
    std::vector<string> tags;
    class Note* next;
};
 
class Storyboard
{
public:
	void addNote(Note* head, string name, string text, std::vector<string> tags);
	void deleteNote(Note* head, string name);
	class Note* searchByTitle(Note* head, string name);
	class Note* searchByText(Note* head, string text);
	class Note* searchByTag(Note* head, std::vector<string> tags);
	
private:
	/*fill in*/
};

void Storyboard::addNote(Note* head, string name, string newText, std::vector<string> tags)
{
    /*Create a new Node*/
    class Note* newNote = new Note;
    newNote->setTitle(name);
    newNote->setText(newText);
    for (vector<string>::iterator it = tags.begin(); it != tags.end(); it++)
    {
        newNote->insertTags(*it);
    }
    
    /*Assign the new node as the head and set the head as the next of new node. 
    If head is NULL, new node becomes the only node in th elist with next as NULL*/
    newNote->setNext(head);
    head = newNote;
}

Note* Storyboard::searchByTitle(Note* head, string name)
{
    /*Safeguard for NULL heads*/
    if(head == NULL)
    {
        return NULL;
    }
    
    class Note* temp = head;
    
    while(temp != NULL)
    {
        if(name == temp->getTitle()) 
        {
            return temp;
        }
        temp = temp->getNext();
    }
    
    return NULL;
}

Note* Storyboard::searchByText(Note* head, string text)
{
    /*Safeguard for NULL heads*/
    if(head == NULL)
    {
        return NULL;
    }
    
    class Note* temp = head;
    
    while(temp != NULL)
    {
        if(text == temp->getText())
        {
            return temp;
        }
        temp = temp->getNext();
    }
    
    return NULL;
}

Note* Storyboard::searchByTag(Note* head, std::vector<string> tags)
{
    int foundTag = 0;
    
    /*Safeguard for empty heads*/
    if(head == NULL)
    {
        return NULL;
    }
    
    class Note* temp = head;
    while(temp != NULL)
    {
        /*Array list traversal, a costly operation*/
        for (vector<string>::iterator it = temp->getTags().begin(); it != temp->getTags().end(); it++)
        {
            for (vector<string>::iterator itLocal = tags.begin(); itLocal != tags.end(); itLocal++)
            {
                if(*it == *itLocal)
                {
                    foundTag++;
                }
            }
        }
        if(foundTag == tags.size())
        {
            return temp;
        }
        else
        {
            temp = temp->getNext();
        }
    }
    cout<<"Node not found";
    return NULL;
}

void Storyboard::deleteNote(Note* head, string name)
{
    class Note* nodeInQuestion = searchByTitle(head, name);
    if(nodeInQuestion != NULL)
    {
        class Note* temp1 = head;
        while(temp1->getNext() != nodeInQuestion)
        {
            temp1 = temp1->getNext();
        }
        temp1->setNext(nodeInQuestion->getNext());
        free(nodeInQuestion);
    }
    cout<<"Node not found";
}

int main()
{
    /*main() is written for unit testing*/
    
    class Note* headNode = NULL;
    
    /*
    * Testcase1 : To test addNode function with empty headNode
    */
    class Storyboard sb;
    vector<string> tags1;
    tags1.push_back("What");
    tags1.push_back("a");
    tags1.push_back("Six");
    
    sb.addNote(headNode, "Storyboard1", "Kohli is playing at the strike and hits a Six", tags1);
    if(headNode != NULL)
    {
        cout<<"Testcase1 passed";
    }
    else
    {
        cout<<"TestCase1 failed";
    }
    
    /*
    * Testcase1 : To test addNode function with empty headNode
    */
    vector<string> tags2;
    tags2.push_back("What");
    tags2.push_back("a");
    tags2.push_back("Goal");
    
    sb.addNote(headNode, "Storyboard2", "Sunil Chetri hits a goal", tags1);
    if(headNode->getNext() != NULL)
    {
        cout<<"Testcase2 passed";
    }
    else
    {
        cout<<"TestCase2 failed";
    }
    
    /*
    * Pass test for searchByTitle
    */
    
    class Note* testNote = sb.searchByTitle(headNode, "Storyboard2");
    if(testNote != NULL)
    {
        if(testNote->getTitle() == "Storyboard2")
        {
            cout<<"TestCase3 passed";
        }
        else
        {
            cout<<"TestCase3 failed";
        }
    }
    else
    {
        cout<<"TestCase3 failed";
    }
    
    /*
    * Fail test for searchByTitle
    */
    
    class Note* testNote2 = sb.searchByTitle(headNode, "Whiteboard1");
    if(testNote2 != NULL)
    {
        if(testNote2->getTitle() == "Whiteboard1")
        {
            cout<<"TestCase3 passed";
        }
        else
        {
            cout<<"TestCase3 failed";
        }
    }
    else
    {
        cout<<"TestCase3 failed";
    }
    
    /*
    * Pass test for searchByText
    */
    
    class Note* testNote3 = sb.searchByText(headNode, "Sunil Chetri hits a goal");
    if(testNote3 != NULL)
    {
        if(testNote3->getTitle() == "Storyboard2")
        {
            cout<<"TestCase4 passed";
        }
        else
        {
            cout<<"TestCase4 failed";
        }
    }
    else
    {
        cout<<"TestCase4 failed";
    }
    
    /*
    * Fail test for searchByText
    */
    
    class Note* testNote4 = sb.searchByText(headNode, "Who is playing");
    if(testNote4 != NULL)
    {
        if(testNote4->getTitle() == "Who is playing")
        {
            cout<<"TestCase5 passed";
        }
        else
        {
            cout<<"TestCase5 failed";
        }
    }
    else
    {
        cout<<"TestCase5 failed";
    }
    
    /*
    * Pass test for searchByTag
    */
    
    vector<string> tags3;
    tags1.push_back("a");
    tags1.push_back("Six");
    
    class Note* testNote6 = sb.searchByTag(headNode, tags3);
    if(testNote6 != NULL)
    {
        cout<<"TestCase6 passed";
    }
    else
    {
        cout<<"TestCase6 failed";
    }
    
    /*
    * Fail test for searchByTag
    */
    
    vector<string> tags4;
    tags1.push_back("Gone");
    tags1.push_back("Six");
    class Note* testNote7 = sb.searchByTag(headNode, tags4);
    if(testNote7 != NULL)
    {
        cout<<"TestCase7 passed";
    }
    else
    {
        cout<<"Check the log"; //This is a different way of testing, not like previous test cases
    }
    
    /*
    * Two tests for delete Node
    */
    
    sb.deleteNote(headNode, "Storyboard2");
    if(headNode->getNext() == NULL)
    {
        cout<<"TestCase8 passed";
    }
    else
    {
        cout<<"testCase8 failed";
    }
    
    sb.deleteNote(headNode, "Whiteboard1");
    cout<<"Check the log for Node not found";
    
    return 0;
}