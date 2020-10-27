

void vartree::deleteTree(vartree_node *root)
{
	if(!root) return;
    for(int i = 0; i <= root->size; i++) deleteTree(root->keys[i]);
	delete root;
}

void vartree::print_proc(vartree_node *Head, int level, int index)
{
    int i;
    if(level > PRINT_LEVEL) return;
    //vartree_node** down = Head->keys;
    //
    printf("%d.%d) ", level, index);
    for(i = 0; i < level; i++) printf("  |");
    Head->print();
    printf("\n");
    //
    int l = (2*ord + 1) < PRINT_CHILD ? (2*ord + 1) : PRINT_CHILD;
    for(i = 0; i < l; i++) { if(Head->keys[i]) print_proc(Head->keys[i], level+1, i); }
}

int vartree::paste_proc(vartree_node*curr, student *&x, vartree_node*&tmp_node)
{
    int i, index = curr->search(x);
    //
    if(curr->keys[0])
        { int ret = paste_proc(curr->keys[index], x, tmp_node); if(ret <= 0) return ret; }
    if(curr->size != 2*ord)
    {
        for(i=curr->size; i>index; i--) { curr->data[i] = curr->data[i-1]; curr->keys[i+1] = curr->keys[i]; }
        curr->data[index] = x;
        curr->keys[index + 1] = tmp_node;
        curr->size++;
        return 0;
    }
    //
    vartree_node*new_node;
    if(!(new_node = new vartree_node(ord))) return -2;
    if(index < ord)
    {
        for(i = 0; i < ord; i++)
        {
            new_node->data[i] = curr->data[i+ord];
            curr->data[i+ord] = nullptr;
            new_node->keys[i] = curr->keys[i+ord];
        }
        new_node->keys[ord] = curr->keys[2*ord];
        for(i=ord; i>index; i--) { curr->data[i] = curr->data[i-1]; curr->keys[i+1] = curr->keys[i]; }
        curr->data[index] = x;
        curr->keys[index+1] = tmp_node;
        x = curr->data[ord];
        curr->data[ord] = nullptr;
    }
    else if(index == ord)
    {
        for(i = 0; i < ord; i++)
        {
            new_node->data[i] = curr->data[i + ord];
            curr->data[i + ord] = nullptr;
            new_node->keys[i + 1] = curr->keys[i + ord + 1];
        }
    new_node->keys[0] = tmp_node;
    }
    else
    {
        index -= ord+1;
        for(i = 0; i < index; i++)
        {
            new_node->data[i] = curr->data[i + ord + 1];
            curr->data[i + ord + 1] = nullptr;
            new_node->keys[i] = curr->keys[i + ord + 1];
        }
        new_node->keys[index] = curr->keys[index + ord + 1];
        new_node->data[index] = x;
        new_node->keys[index + 1] = tmp_node;
        for(i++; i < ord; i++)
        {
            new_node->data[i] = curr->data[i + ord];
            curr->data[i + ord] = nullptr;
            new_node->keys[i + 1] = curr->keys[i + ord + 1];
        }
        x = curr->data[ord];
        curr->data[ord] = nullptr;
    }
    curr->size = new_node->size = ord;
    tmp_node = new_node;
    return 1;
}

int vartree::paste(student *x)
{
    if(!root)
    {
        if(!(root = new vartree_node(ord))) { delete x; return -2; }
        root->data[0] = x;
        root->size = 1;
        return 0;
    }
    //
    current = nullptr;
    int ret = paste_proc(root, x, current);
    if(ret < 0) { delete x; return -2; }
    if(!ret) return 0;
    //
    vartree_node*new_node;
    if(!(new_node = new vartree_node(ord))) { delete x; return -2; }
    new_node->keys[0] = root; new_node->keys[1] = current;
    new_node->data[0] = x;
    new_node->size = 1;
    root = new_node;
    return 0;
}

int vartree::read(FILE *fp)
{
    student *new_student;
    int ret;
    deleteTree(root);
    while(true)
    {
        if(!(new_student = new student)) return -2;
        ret = new_student->read(fp);
        if(ret < 0){delete new_student; return -1;}
        if(ret > 0){delete new_student; break;}
        if(paste(new_student)) return -2;
    }
    return 0;
}
