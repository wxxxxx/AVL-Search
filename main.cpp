#include <QCoreApplication>
#include <iostream>
using namespace std;

#define LH +1
#define EH 0
#define RH -1

typedef struct BiTNode
{
    int data;
    int bf;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void L_Rotate(BiTree *p)
{
    BiTree R;
    R = (*p)->rchild;
    (*p)->rchild = R->lchild;
    R->lchild = *p;
    *p = R;
}

void R_Rotate(BiTree *p)
{
    BiTree L;
    L = (*p)->lchild;
    (*p)->lchild = L->rchild;
    L->rchild = *p;
    *p = L;
}

void LeftBalance(BiTree *T)
{
    BiTree L,Lr;
    L = (*T)->lchild;
    switch(L->bf)
    {
    case LH:
        (*T)->bf = L->bf = EH;
        R_Rotate(T);
        break;
    case RH:
        Lr = L->rchild;
        switch(Lr->bf)
        {
        case LH:
            (*T)->bf = RH;
            L->bf = EH;
            break;
        case EH:
            (*T)->bf = L->bf = EH;
            break;
        case RH:
            (*T)->bf = EH;
            L->bf = LH;
            break;
        }
        Lr->bf = EH;
        L_Rotate(&(*T)->lchild);
        R_Rotate(T);
    }
}

void RightBalance(BiTree *T)
{
    BiTree R,Rl;
    R = (*T)->rchild;
    switch(R->bf)
    {
    case RH:
        (*T)->bf = R->bf = EH;
        L_Rotate(T);
        break;

    case LH:
        Rl = R->lchild;
        switch(Rl->bf)
        {
        case LH:
            (*T)->bf = EH;
            R->bf = RH;
            break;
        case EH:
            (*T)->bf = EH;
            R->bf = EH;
            break;
        case RH:
            (*T)->bf = LH;
            R->bf = EH;
            break;
        }
        Rl->bf = EH;
        R_Rotate(&(*T)->rchild);
        L_Rotate(T);
    }
}


bool InsertAVL(BiTree *T,int e,bool *taller)
{
    if(!*T)
    {
        *T = (BiTree) malloc (sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = nullptr;
        (*T)->bf = EH;
        *taller = true;
    }
    else
    {
        if(e == (*T)->data)
        {
            *taller = false;
            return false;
        }
        if(e < (*T)->data)
        {
            if(!InsertAVL(&(*T)->lchild, e, taller))
                return false;
            if(*taller)
            {
                switch((*T)->bf)
                {
                case LH:
                    LeftBalance(T);
                    *taller = false;
                    break;
                case EH:
                    (*T)->bf = LH;
                    *taller = true;
                    break;
                case RH:
                    (*T)->bf = EH;
                    *taller = false;
                    break;
                }
            }
        }
        else
        {
            if(!InsertAVL(&(*T)->rchild, e, taller))
                return false;
            if(*taller)
            {
                switch((*T)->bf)
                {
                case LH:
                    (*T)->bf = EH;
                    *taller = false;
                    break;
                case EH:
                    (*T)->bf = RH;
                    *taller = true;
                    break;
                case RH:
                    RightBalance(T);
                    *taller = false;
                    break;
                }
            }
        }
    }
    return true;
}

void fSearchAVL(BiTree *T)
{
    if(*T == nullptr)
        return;
    cout<<(*T)->data<<" ";
    fSearchAVL(&(*T)->lchild);
    fSearchAVL(&(*T)->rchild);
}

void SearchAVL(BiTree *T)
{
    if(*T == nullptr)
        return;
    SearchAVL(&(*T)->lchild);
    cout<<(*T)->data<<" ";
    SearchAVL(&(*T)->rchild);
}

void bSearchAVL(BiTree *T)
{
    if(*T == nullptr)
        return;
    bSearchAVL(&(*T)->lchild);
    bSearchAVL(&(*T)->rchild);
    cout<<(*T)->data<<" ";
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int i;
    int b[10] = {3,2,1,4,5,6,7,10,9,8};
    BiTree T = nullptr;
    bool taller;
    for(i = 0; i < 10; i++)
    {
        InsertAVL(&T, b[i],&taller);
    }

    cout<<"forSearch:";
    fSearchAVL(&T);
    cout<<endl;

    cout<<"midSearch:";
    SearchAVL(&T);
    cout<<endl;

    cout<<"bacSearch:";
    bSearchAVL(&T);
    cout<<endl;

    return a.exec();
}

