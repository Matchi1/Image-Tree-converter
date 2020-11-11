#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/Display_qt.h"

void write_beginning(FILE *f){
    fprintf(f, "digraph arbre {\n");
    fprintf(f, "    node [shape=record, height=.1]\n");
    fprintf(f, "    edge[tailclip=false, arrowtail = dot, dir=both];\n");
    fprintf(f, "\n");
}

void write_qt(FILE *f, Quadtree qt){

    if(NULL != qt){
		if(qt->rgba != NULL && qt->pixel != NULL)
			fprintf(f, "    n%p [label=\"<sonNW> | <sonNE> | <x> %d | <y> %d | <r> %d | <g> %d | <b> %d | <a> %d | <sonSE> | <sonSW>\"]\n", 
				(void*)qt, qt->pixel->x, qt->pixel->y, qt->rgba->r, qt->rgba->g, qt->rgba->b, qt->rgba->a);
		else if(qt->rgba != NULL) 
			fprintf(f, "    n%p [label=\"<sonNW> | <sonNE> | <x> | <y> | <r> %d | <g> %d | <b> %d | <a> %d | <sonSE> | <sonSW>\"]\n", 
				(void*)qt, qt->rgba->r, qt->rgba->g, qt->rgba->b, qt->rgba->a);
		else  
			fprintf(f, "    n%p [label=\"<sonNW> | <sonNE> | <x> | <y> | <r> | <g> | <b> | <a> | <sonSE> | <sonSW>\"]\n", 
				(void*)qt);

        if(!is_leave(qt)){
            fprintf(f, "    n%p:sonNW:c -> n%p:g;\n", (void*)qt, (void*)qt->sonNW);
            write_qt(f, qt->sonNW);
            fprintf(f, "    n%p:sonNE:c -> n%p:g;\n", (void*)qt, (void*)qt->sonNE);
            write_qt(f, qt->sonNE);
            fprintf(f, "    n%p:sonSE:c -> n%p:g;\n", (void*)qt, (void*)qt->sonSE);
            write_qt(f, qt->sonSE);
            fprintf(f, "    n%p:sonSW:c -> n%p:g;\n", (void*)qt, (void*)qt->sonSW);
            write_qt(f, qt->sonSW);
        }
    }
}

void write_end(FILE *f){
    fprintf(f, "}");
}

void draw(FILE* f, Quadtree qt){
    write_beginning(f);
    write_qt(f, qt);
    write_end(f);
}

int create_PDF(char* dot, char* pdf, Quadtree qt){
    int len;
    char* cmd;
    FILE* out;

    out = fopen(dot, "w");
    draw(out, qt);
    fclose(out);
    len = strlen(dot) + strlen(pdf) + 15;
    cmd = (char*)malloc(sizeof(char) * len);
    if(cmd == NULL)
        return 0;

    strcpy(cmd, "dot -Tpdf ");
    strcat(cmd, dot);
    strcat(cmd, " -o ");
    strcat(cmd, pdf);
    system(cmd);
    return 1;
}

void display_qt_pdf(Quadtree qt){
    char* pdf;
    char* dot;

    pdf = "tmp.pdf";
    dot = "tmp.dot";

    create_PDF(dot, pdf, qt);
    system("evince tmp.pdf &");
}
