//
//  NewHandlerTemplate.h
//  myLib
//
//  Created by XinquanZhou on 10/25/15.
//  Copyright © 2015 Xinquan Zhou. All rights reserved.
//

#ifndef NewHandlerTemplate_h
#define NewHandlerTemplate_h

class NewHandlerHolder {
public:
    explicit NewHandlerHolder(std::new_handler nh):handler(nh){}
    
    ~NewHandlerHolder(){
        std::set_new_handler(handler);
    }
private:
    std::new_handler handler;
    NewHandlerHolder(const NewHandlerHolder&);
    NewHandlerHolder& operator=(const NewHandlerHolder&);
};

template <class T>
class NewHandlerTemplate {
public:
    static std::new_handler set_new_handler(std::new_handler p) throw();
    static void *operator new(std::size_t size) throw(std::bad_alloc);
    
private:
    static std::new_handler currentHandler;
};

template <class T>
std::new_handler NewHandlerTemplate<T>::set_new_handler(std::new_handler p) throw() {
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}

template <class T>
void *  NewHandlerTemplate<T>::operator new(std::size_t size) throw(std::bad_alloc) {
    NewHandlerHolder h(std::set_new_handler(currentHandler));
    return ::operator new(size);
}

template <class T>
std::new_handler NewHandlerTemplate<T>::currentHandler = 0;


// usage
//class derive : public NewHandlerTemplate<derive>{
//};
//
//void outOfMem();
//
//derive::set_new_handler(outOfMem);


#endif /* NewHandlerTemplate_h */
