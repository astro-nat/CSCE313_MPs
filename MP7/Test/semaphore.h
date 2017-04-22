/* 
    File: semaphore.H

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 08/02/11

*/

#ifndef _semaphore_H_                   // include file only once
#define _semaphore_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <pthread.h>
#include <string>
#include <iostream>

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS   s e m a p h o r e  */
/*--------------------------------------------------------------------------*/

class semaphore {
private:
    
    int count;
    pthread_mutex_t mut;
    pthread_cond_t cond;

public:

    /* -- CONSTRUCTOR/DESTRUCTOR */

    semaphore(int _val) {
        set_val(_val);
	}
    
    semaphore() {
        pthread_mutex_init(&mut, NULL);
        pthread_cond_init(&cond, NULL);
    }

    ~semaphore(){
		pthread_mutex_destroy(&mut);
		pthread_cond_destroy(&cond);
    }

    /* -- SEMAPHORE OPERATIONS */
    
    void set_val(int _val) {
        count = _val;
    }
    
    void P() {
        pthread_mutex_lock(&mut);
        count--;
        if(count < 0) {
            pthread_cond_wait(&cond, &mut);
        }
        pthread_mutex_unlock(&mut);
    }

    void V() {
        pthread_mutex_lock(&mut);
        count++;
        if(count<= 0)  {
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mut);
    }
};

#endif


