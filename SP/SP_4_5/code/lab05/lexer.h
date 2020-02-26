//                 lexer.h 2019
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"
//********************************************
//*        Developed by  xxx		     *
//*             (c)  2019                    *
//********************************************
class tLexer:public tBaseLexer{
public:
// ������������ ��� ������������
 std::string Authentication()const{
                     return "pys"
                +std::string("2019");}
//�����������
 tLexer():tBaseLexer(){
//������� ��������:

//  ���� Azero
    addstr  (Azero,0,"+-", 2);
    addstr  (Azero,0,"0",  1);
    addstr  (Azero,2,"0",  1);
  Azero.final(1);

//________________________________________

// �����
        addrange(Adec, 0, '1', '9', 6);
        addstr(Adec, 0, "+", 7);
        addstr(Adec, 0, "-", 7);
        addstr(Adec, 7, "0", 1);
        addrange(Adec, 7, '1', '9', 6);
        addstr(Adec, 0, "0", 1);
        addstr(Adec, 1, ".", 2);
        addstr(Adec, 1, "e", 3);
        addstr(Adec, 1, "E", 3);
        addrange(Adec, 6, '0', '9', 6);
        addstr(Adec, 6, ".", 2);
        addrange(Adec, 2, '0', '9', 2);

        addstr(Adec, 6, "e", 3);
        addstr(Adec, 6, "E", 3);
        addstr(Adec, 2, "e", 3);
        addstr(Adec, 2, "E", 3);
        addstr(Adec, 3, "+", 4);
        addstr(Adec, 3, "-", 4);
        addrange(Adec, 4, '0', '9', 5);
        addrange(Adec, 5, '0', '9', 5);

//......................
        Adec.final(1);
        Adec.final(2);
        Adec.final(5);
        Adec.final(6);
//________________________________________

// �������������
	addstr  (Aid,0,"?",2);
	addstr  (Aid,0,"!",1);
	addrange(Aid,0,'a','z',1);
	addrange(Aid,0,'A','Z',1);
	
	
	addstr  (Aid,1,"!",1);
	addstr  (Aid,1,"-",1);
	addrange(Aid,1,'a','z',1);
	addrange(Aid,1,'A','Z',1);
	addrange(Aid,1,'0','9',1);
	addstr  (Aid,1,"?",2);

	addstr  (Aid,2,"?",2);
	addrange(Aid,2,'0','9',1);
	addstr  (Aid,2,"!",1);
    addrange(Aid,2,'a','z',1);
    addrange(Aid,2,'A','Z',1);
    addstr  (Aid,2,"-",3);

    addstr  (Aid,3,"!",1);
    addstr  (Aid,3,"?",2);
    addrange(Aid,3,'a','z',1);
    addrange(Aid,3,'A','Z',1);
    addrange(Aid,3,'0','9',1);
    addstr  (Aid,3,"-",4);

  Aid.final(1);
  Aid.final(3);
//________________________________________

// ������������� ���������
    addstr  (Aidq,0,"!",   1);
	addstr  (Aidq,0,"-",   1);
	addrange(Aidq,0,'a','z',1);
	addrange(Aidq,0,'A','Z',1);
	addstr  (Aidq,0,"?",   2);
	
	addrange(Aidq,1,'a','z',1);
	addrange(Aidq,1,'A','Z',1);
	addrange(Aidq,1,'0','9',1);
    addstr  (Aidq,1,"!",   1);
	addstr  (Aidq,1,"-",   1);
	addstr  (Aidq,1,"?",   2);
	
	
	addrange(Aidq,2,'a','z',1);
	addrange(Aidq,2,'A','Z',1);
	addrange(Aidq,2,'0','9',1);
    addstr  (Aidq,2,"!",   1);
	addstr  (Aidq,2,"-",   1);
	addstr  (Aidq,2,"?",   3);
	
  Aidq.final(2);
}
};
#endif

