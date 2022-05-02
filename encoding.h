#pragma once
#include "alg.h"
#include <iostream>
#include <math.h>

template<class T>
struct tree {
    struct node {
        br3nder::List<T> list;
        node *left;
        node *right;

        node(br3nder::List<T> list) : list(list), left(nullptr), right(nullptr) {};

        node(br3nder::List<T> *list) : list(*list), left(nullptr), right(nullptr) {};
    };

    node root;

    tree(br3nder::List<T> list) : root(list) {};

    std::string find(T *e){
        std::string s = "";
        node* cur_node = &root;
        while(cur_node != nullptr && cur_node->left && cur_node->right){
            if(cur_node->left->list.find(e)){
                s += '0';
                cur_node = cur_node->left;
            }
            else {
                s += "1";
                cur_node = cur_node->right;
            }
        }
        return s;
    }

    char reverse_find(std::string *s){
        node* cur_node = &root;
        std::string s2 = *s;
        while(cur_node->left || cur_node->right){
            if(s2[0] == '0'){
                s->erase(0,1);
                s2.erase(0,1);
                cur_node = cur_node->left;
            }
            else {
                s->erase(0,1);
                s2.erase(0,1);
                cur_node = cur_node->right;
            }
        }
        br3nder::pair<char, int> *p = cur_node->list.get();
        return p->data1;
    }

    int center_of_list(node *n) {
        if (n->list.size() == 2)
            return 0;
        else if (n->list.size() & 2 == 0)
            return ceil(n->list.size() / 2) - 1;
        else
            return ceil(n->list.size() / 2);
    }

    void make_tree(node *n) {
        int center = center_of_list(n);
        br3nder::pair<br3nder::List<br3nder::pair<char, int>>, br3nder::List<br3nder::pair<char, int>>> pair = n->list.split(
                center);

        n->left = new node(pair.data1);
        n->right = new node(pair.data2);
        if(n->list.size() != 2){ //т.к. если длина = 2, то будет по одному ребенку и все: это последний узел, потом уже листья
            if(n->left->list.size() != 1)
                make_tree(n->left);
            if(n->right->list.size() != 1)
                make_tree(n->right);
        }

    };
};

std::string show_alphabet(std::string s, tree<br3nder::pair<char, int>> *tree){
    br3nder::List<br3nder::pair<char, int>> l = br3nder::list_count_symbols(s);
    std::string out = "";
    std::string c;
    for(int i = 0; i < l.size(); i++){
        std::cout << l.get_by_index(i)->data1;
        out += l.get_by_index(i)->data1;
        c = tree->find(new br3nder::pair<char, int>(s[i], br3nder::count_symbols(s, s[i])));
        std::cout << " " << c << std::endl;
        out +=c;
    }
    return out;
}

br3nder::pair<std::string, tree<br3nder::pair<char, int>>> encode(std::string str) {
    br3nder::List<br3nder::pair<char, int>> list = br3nder::list_count_symbols(str);
    tree<br3nder::pair<char, int>> tree(list);
    tree.make_tree(&tree.root);
    std::string code = "";
    for (int i = 0; i < str.length(); i++) {
        std::string c = "";
        c = tree.find(new br3nder::pair<char, int>(str[i], br3nder::count_symbols(str, str[i])));
        code += c;
    }
    br3nder::pair<std::string, ::tree<br3nder::pair<char, int>>> pair(code, tree);
    return pair;
}

std::string decode(std::string encode_str, tree<br3nder::pair<char, int>> *tree) {
    std::string s = encode_str;
    std::string decode_str = "";
    while(!s.empty()){
        decode_str += tree->reverse_find(&s);
    }
    return decode_str;
}
