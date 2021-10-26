#include <iostream>
#include <fstream>
#include <string.h>
#include <malloc.h>
#include <unordered_map>
#include <sstream>
#include <vector>

using std::string;
/* using std::cout; */
using std::ifstream;
using std::ofstream;

char s[128];
std::vector<std::string> vec;


int lex() {
    std::unordered_map<std::string, std::string> umap( 13 );
	umap["const"]	= "CONSTTK";
	umap["int"]	= "INTTK";
	umap["char"]	= "CHARTK";
	umap["void"]	= "VOIDTK";
	umap["main"]	= "MAINTK";
	umap["if"]	= "IFTK";
	umap["else"]	= "ELSETK";
	umap["do"]	= "DOTK";
	umap["while"]	= "WHILETK";
	umap["for"]	= "FORTK";
	umap["scanf"]	= "SCANFTK";
	umap["printf"]	= "PRINTFTK";
	umap["return"]	= "RETURNTK";
	FILE	* in;
	FILE	* fp;
	in	= fopen( "testfile.txt", "r" );
	fp	= fopen( "output.txt", "w+" );
	char	CHAR;
	char	* TOKEN = (char *) malloc( sizeof(char) * 128 );
	while ( (CHAR = fgetc( in ) ) != EOF )
	{
		while ( CHAR != ' ' && (CHAR != '\n') && (CHAR != '\r') && CHAR != '\t' )
		{
			if ( (CHAR >= 'A' && CHAR <= 'Z') || (CHAR >= 'a' && CHAR <= 'z') || CHAR == '_' )
			{
				int k = 0;
				do
				{
					TOKEN[k] = CHAR;
					k++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR != ' ' && CHAR != '\n' && ( (CHAR >= 'A' && CHAR <= 'Z') || (CHAR >= 'a' && CHAR <= 'z') || CHAR == '_') );
				if ( CHAR >= '0' && CHAR <= '9' )
				{
					do
					{
						TOKEN[k] = CHAR;
						k++;
					}
					while ( (CHAR = fgetc( in ) ) != EOF && CHAR != ' ' && CHAR != '\n' && (CHAR >= '0' && CHAR <= '9') );
				}
				TOKEN[k] = '\0';
				std::unordered_map<string, string>::iterator iter = umap.find( TOKEN );

				if ( iter != umap.end() )
				{
					fprintf( fp, "%s %s\n", iter->second.c_str(), TOKEN );
				} else{
					fprintf( fp, "%s %s\n", "IDENFR", TOKEN );
					/* cout<<"IDENFR"<<' '<<TOKEN<<"\n"; */
				}
			}

			if ( CHAR >= '0' && CHAR <= '9' )
			{
				int j = 0;
				do
				{
					TOKEN[j] = CHAR;
					j++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR != ' ' && CHAR != '\n' && (CHAR >= '0' && CHAR <= '9') );
				TOKEN[j] = '\0';
				fprintf( fp, "%s %s\n", "INTCON", TOKEN );
			}
			if ( CHAR == '\"' )
			{
				int i = 0;
				do
				{
					TOKEN[i] = CHAR;
					i++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR != '\"' && CHAR != '\'' );
				TOKEN[i]	= '\0';
				TOKEN[0]	= ' ';
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
				fprintf( fp, "%s%s\n", "STRCON", TOKEN );
				/* cout<<"STRCON"<<' '<<TOKEN<<"\n"; */
			}
			if ( CHAR == '\'' )
			{
				int i = 0;
				do
				{
					TOKEN[i] = CHAR;
					i++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR != '\"' && CHAR != '\'' );
				TOKEN[i]	= '\0';
				TOKEN[0]	= ' ';

				CHAR = fgetc( in );
				fprintf( fp, "%s%s\n", "CHARCON", TOKEN );
				/* cout<<"CHARCON"<<' '<<TOKEN<<"\n"; */
			}
			if ( CHAR == '<' )
			{
				int i = 0;

				do
				{
					TOKEN[i] = CHAR;
					i++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR == '=' && CHAR != '\n' && CHAR != ' ' );
				char a = TOKEN[1];
				TOKEN[i] = '\0';
				if ( a == '=' )
				{
					fprintf( fp, "%s %s\n", "LEQ", TOKEN );
					/* cout<<"LEQ"<<' '<<TOKEN<<"\n"; */
				} else {
					fprintf( fp, "%s %s\n", "LSS", TOKEN );
					/* cout<<"LSS"<<' '<<TOKEN<<"\n"; */
				}
			}
			if ( CHAR == '>' )
			{
				int i = 0;

				do
				{
					TOKEN[i] = CHAR;
					i++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR == '=' && CHAR != '\n' && CHAR != ' ' );
				char a = TOKEN[1];
				TOKEN[i] = '\0';
				if ( a == '=' )
				{
					fprintf( fp, "%s %s\n", "GEQ", TOKEN );
					/* cout<<"GEQ"<<' '<<TOKEN<<"\n"; */
				} else {
					fprintf( fp, "%s %s\n", "GRE", TOKEN );
					/* cout<<"GRE"<<' '<<TOKEN<<"\n"; */
				}
			}
			if ( CHAR == '=' )
			{
				int i = 0;

				do
				{
					TOKEN[i] = CHAR;
					i++;
				}
				while ( (CHAR = fgetc( in ) ) != EOF && CHAR == '=' && CHAR != '\n' && CHAR != ' ' );
				char a = TOKEN[1];
				TOKEN[i] = '\0';
				if ( a == '=' )
				{
					fprintf( fp, "%s %s\n", "EQL", TOKEN );
					/* cout<<"EQL"<<' '<<TOKEN<<"\n"; */
				} else {
					fprintf( fp, "%s %s\n", "ASSIGN", TOKEN );
					/* cout<<"ASSIGN"<<' '<<TOKEN<<"\n"; */
				}
			}
			if ( CHAR == '!' )
			{
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    	       	    fclose(in);
					return(1);
				}
				if ( CHAR == '=' )
				{
					fprintf( fp, "%s %s\n", "NEQ", "!=" );
					/* cout<<"NEQ"<<' '<<"!="<<"\n"; */
				}
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '+' )
			{
				fprintf( fp, "%s %c\n", "PLUS", CHAR );
				/* cout<<"PLUS"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '-' )
			{
				fprintf( fp, "%s %c\n", "MINU", CHAR );
				/* cout<<"MINU"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '*' )
			{
				fprintf( fp, "%s %c\n", "MULT", CHAR );
				/* cout<<"MULT"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '/' )
			{
				fprintf( fp, "%s %c\n", "DIV", CHAR );
				/* cout<<"DIV"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    	     	    fclose(in);
					return(1);
				}
			}
			if ( CHAR == ',' )
			{
				fprintf( fp, "%s %c\n", "COMMA", CHAR );
				/* cout<<"COMMA"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '{' )
			{
				fprintf( fp, "%s %c\n", "LBRACE", CHAR );
				/* cout<<"LBRACE"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '[' )
			{
				fprintf( fp, "%s %c\n", "LBRACK", CHAR );
				/* cout<<"LBRACK"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == '(' )
			{
				fprintf( fp, "%s %c\n", "LPARENT", CHAR );
				/* cout<<"LPARENT"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == ')' )
			{
				fprintf( fp, "%s %c\n", "RPARENT", CHAR );
				/* cout<<"RPARENT"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}

			if ( CHAR == ']' )
			{
				fprintf( fp, "%s %c\n", "RBRACK", CHAR );
				/* cout<<"RBRACK"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}

			if ( CHAR == '}' )
			{
				fprintf( fp, "%s %c\n", "RBRACE", CHAR );
				/* cout<<"RBRACE"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
			if ( CHAR == ';' )
			{
				fprintf( fp, "%s %c\n", "SEMICN", CHAR );
				/* cout<<"SEMICN"<<' '<<CHAR<<"\n"; */
				if ( (CHAR = fgetc( in ) ) == EOF )
				{
				    fclose(fp);
                    		    fclose(in);
					return(1);
				}
			}
		}
	}
	fclose(fp);
	fclose(in);
	return (1);
}

int parseExpression(char buf[1024][128], int loc, FILE* out,int flag);
int parseValueParmMap(char buf[1024][128], int loc, FILE* out,int flag);
int parseStmt (char buf[1024][128], int loc, FILE* out, int flag);
int parseStmtCol(char buf[1024][128], int loc, FILE* out,int flag,int fuck);

int parseString(char buf[1024][128],int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("STRCON",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        loc++;
    }
    if(flag<loc){
        fprintf(out, "%s\n", "<字符串>");
    }
    return loc;
}

int parseUnsignedInt(char buf[1024][128],int loc, FILE* out) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("INTCON",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        //std::cout<<buf[loc];
        fprintf(out, "%s\n", "<无符号整数>");
        return loc+1;
    }
    return loc;
}

int parseInteger(char buf[1024][128],int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("MINU",s)==0||strcmp("PLUS",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseUnsignedInt(buf,loc+1,out);

    } else {
        loc = parseUnsignedInt(buf,loc,out);
    }
    if(flag < loc){
        fprintf(out, "%s\n", "<整数>");
    }
    return loc;
}

int parseIdenInt(char buf[1024][128],int loc, FILE* out,int mode) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IDENFR",s)==0) {
        fprintf( out, "%s", buf[loc]);
        //std::cout<<buf[loc];
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(mode==1) {
            if(strcmp("LBRACK",s)==0) {
                fprintf(out,  "%s", buf[loc+1]);
                loc+=2;
                loc = parseUnsignedInt(buf,loc,out);
                std::istringstream ss2(buf[loc]);
                ss2>>s;
                if(strcmp("RBRACK",s)==0) {
                    fprintf(out,  "%s", buf[loc]);
                }
            }else if(strcmp("ASSIGN",s)==0) {
                fprintf(out,  "%s", buf[loc+1]);
                //std::cout<<buf[loc+1];
                loc = parseInteger(buf,loc+2,out,loc+2);
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("CHARCON",s)==0) {
                    fprintf(out,  "%s", buf[loc]);
                    loc++;
                }
                return parseIdenInt(buf,loc,out,mode);
            }
            return parseIdenInt(buf,loc+1,out,mode);
        }
        if(strcmp("ASSIGN",s)==0) {
            fprintf(out,  "%s", buf[loc+1]);
            //std::cout<<buf[loc+1];
            loc = parseInteger(buf,loc+2,out,loc+2);
            std::istringstream ss3(buf[loc]);
            ss3>>s;
            if(strcmp("CHARCON",s)==0) {
                fprintf(out,  "%s", buf[loc]);
                loc++;
            }
            return parseIdenInt(buf,loc,out,mode);
        }
        loc++;
    } else if(strcmp("COMMA",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseIdenInt(buf,loc+1,out,mode);
        return loc;
    }
    return loc;

}


int parseConstDef(char buf[1024][128], int loc, FILE* out) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("INTTK",s)==0){
        fprintf(out, "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseIdenInt(buf,loc+1,out,1);

    } else if(strcmp("CHARTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseIdenInt(buf,loc+1,out,1);
    }
    fprintf(out, "%s\n", "<常量定义>");
    return loc;
}



int parseConstDes(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("CONSTTK",s)==0){
        fprintf(out,  "%s", buf[loc]);
        loc = parseConstDef(buf,loc+1,out);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("SEMICN",s)==0){
            fprintf(out,  "%s", buf[loc]);
            return parseConstDes(buf,loc+1,out,flag);
        }
        //error: expect ';'
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<常量说明>");
    }
    return loc;
}

int parseVarDefOrParamForm(char buf[1024][128], int loc, FILE* out,int mode) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("INTTK",s)==0){
        fprintf(out, "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseIdenInt(buf,loc+1,out,mode);

    } else if(strcmp("CHARTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseIdenInt(buf,loc+1,out,mode);
    }
    if(mode==1){
        fprintf(out, "%s\n", "<变量定义>");
    } else if(mode == 2) {
        if(strcmp("COMMA",s)==0) {
            fprintf(out,  "%s", buf[loc]);
            //std::cout<<buf[loc];
            loc = parseVarDefOrParamForm(buf,loc+1,out,2);
            return loc;
        }
        fprintf(out, "%s\n", "<参数表>");
    }

    return loc;
}

int parseVarDes(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss2(buf[loc]);
    char temp[64];
    ss2>>temp;
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if((strcmp("INTTK",temp)==0||strcmp("CHARTK",temp)==0)&&(strcmp("SEMICN",s)==0||strcmp("ASSIGN",s)==0||strcmp("COMMA",s)==0||strcmp("LBRACK",s)==0)) {
        loc = parseVarDefOrParamForm(buf,loc,out,1);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("SEMICN",s)==0){
            fprintf(out,  "%s", buf[loc]);
            return parseVarDes(buf,loc+1,out,flag);
        }
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<变量说明>");
    }
    return loc;
}


int parseHaveRetCall(char buf[1024][128], int loc, FILE* out,int flag){
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IDENFR",s)==0) {
        fprintf(out, "%s", buf[loc]);
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc+1]);
            int temp = parseValueParmMap(buf,loc+2,out,loc+2);
            if(temp==loc+2){
                fprintf(out,  "%s\n", "<值参数表>");
            }
            loc = temp;
            std::istringstream ss3(buf[loc]);
            ss3>>s;
            if(strcmp("RPARENT",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;

            }
            //error
        }
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<有返回值的函数调用语句>");
    }
    return loc;
}


int parseHaveNoRetCall(char buf[1024][128], int loc, FILE* out,int flag){
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IDENFR",s)==0) {
        fprintf(out, "%s", buf[loc]);
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc+1]);
            int temp = parseValueParmMap(buf,loc+2,out,loc+2);
            if(temp==loc+2){
                fprintf(out,  "%s\n", "<值参数表>");
            }
            loc=temp;
            std::istringstream ss3(buf[loc]);
            ss3>>s;
            if(strcmp("RPARENT",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;

            }
            //error
        }
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<无返回值函数调用语句>");
    }
    return loc;
}

int parseFactors(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IDENFR",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("LBRACK",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc = parseExpression(buf,loc+1,out,loc+1);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("RBRACK",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;
            }
            //error: expect ']'
        } else if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc]);
            int temp = parseValueParmMap(buf,loc+1,out,loc+1);
            if(temp==loc+1) {
                temp = parseExpression(buf,loc+1,out,loc+1);

                std::istringstream ss3(buf[temp]);
                ss3>>s;
                if(strcmp("RPARENT",s)==0) {
                    if(temp==loc+1) {
                        fprintf(out,  "%s\n", "<值参数表>");
                        fprintf(out, "%s", buf[temp]);
                        fprintf(out,  "%s\n", "<有返回值函数调用语句>");
                    }
                    loc=temp+1;
                }
            } else {
                loc = temp;
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("RPARENT",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                    fprintf(out,  "%s\n", "<有返回值函数调用语句>");
                }
            }

            //error
        }
    } else if (strcmp("LPARENT",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc = parseExpression(buf,loc+1,out,loc+1);
        std::istringstream ss2(buf[loc]);
        ss2>>s;
        if (strcmp("RPARENT",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc++;
        }
    } else if(strcmp("PLUS",s)==0||strcmp("MINU",s)==0||strcmp("INTCON",s)==0) {
        loc = parseInteger(buf,loc,out,loc);
    } else if(strcmp("CHARCON",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
    }

    if(flag<loc){
        fprintf(out,  "%s\n", "<因子>");
    }
    return loc;
}

int parseTerms(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseFactors(buf,loc,out,loc);
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("DIV",s)==0||strcmp("MULT",s)==0) {
        fprintf(out, "%s", buf[loc]);
        return parseTerms(buf,loc+1,out,flag);
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<项>");
    }
    return loc;
}

int parseExpression(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("MINU",s)==0||strcmp("PLUS",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        //std::cout<<buf[loc];
        loc = parseTerms(buf,loc+1,out,loc+1);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        while(strcmp("MINU",s)==0||strcmp("PLUS",s)==0) {
            fprintf(out,  "%s", buf[loc]);
            loc = parseTerms(buf,loc+1,out,loc+1);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
        }
    }
    loc = parseTerms(buf,loc,out,loc);
    std::istringstream ss1(buf[loc]);
    ss1>>s;
    while(strcmp("MINU",s)==0||strcmp("PLUS",s)==0) {
        fprintf(out,  "%s", buf[loc]);
        loc = parseTerms(buf,loc+1,out,loc+1);
        std::istringstream ss2(buf[loc]);
        ss2>>s;
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<表达式>");
    }
    return loc;
}



int parseDeclareHead(char buf[1024][128], int loc, FILE* out) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("INTTK",s)==0){
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0) {
            fprintf(out, "%s", buf[loc]);
            std::string tempstr="";
            int i = 0;
            while(buf[loc][i]!='\n'&&buf[loc][i]!='\0'){
                tempstr+=buf[loc][i];
                i++;
            }
            vec.push_back(tempstr);
            loc++;
        }

    } else if(strcmp("CHARTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0) {
            fprintf(out, "%s", buf[loc]);
            std::string tempstr="";
            int i = 0;
            while(buf[loc][i]!='\n'&&buf[loc][i]!='\0'){
                tempstr+=buf[loc][i];
                i++;
            }
            vec.push_back(tempstr);
            loc++;
        }
    }
    fprintf(out,  "%s\n", "<声明头部>");
    return loc;
}

int parseValueParmMap(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseExpression(buf,loc,out,loc);
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("COMMA",s)==0) {
        fprintf(out, "%s", buf[loc]);
        return parseValueParmMap(buf,loc+1,out,flag);
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<值参数表>");
    }
    return loc;
}



int parseConditon(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseExpression(buf,loc,out,loc);
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("LSS",s)==0||strcmp("LEQ",s)==0||strcmp("GEQ",s)==0||strcmp("GRE",s)==0||strcmp("EQL",s)==0||strcmp("NEQ",s)==0){
        fprintf(out,  "%s", buf[loc]);
        loc = parseExpression(buf,loc+1,out,loc+1);
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<条件>");
    }

    return loc;
}


int parseIfStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IFTK",s)==0){
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0){
            fprintf(out, "%s", buf[loc]);
            loc++;
            loc = parseConditon(buf,loc,out,loc);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("RPARENT",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;
                loc = parseStmt(buf,loc,out,loc);
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("ELSETK",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                    loc = parseStmt(buf,loc,out,loc);
                }
            }
        }
        // error: expect '('
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<条件语句>");
    }
    return loc;
}

int parseLoopStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("WHILETK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc+1]);
            loc = parseConditon(buf,loc+2,out,loc+2);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("RPARENT",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc = parseStmt(buf,loc+1,out,loc+1);
            }
            //error
        }
    } else if(strcmp("DOTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc = parseStmt(buf,loc+1,out,loc+1);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("WHILETK",s)==0) {
            fprintf(out, "%s", buf[loc]);
            std::istringstream ss2(buf[loc+1]);
            ss2>>s;
            if(strcmp("LPARENT",s)==0) {
                fprintf(out, "%s", buf[loc+1]);
                loc = parseConditon(buf,loc+2,out,loc+2);
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("RPARENT",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                }
                //error
            }
        }


    } else if(strcmp("FORTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc+1]);
            std::istringstream ss2(buf[loc+2]);
            ss2>>s;
            if(strcmp("IDENFR",s)==0) {
                fprintf(out, "%s", buf[loc+2]);
                std::istringstream ss4(buf[loc+3]);
                ss4>>s;
                if(strcmp("ASSIGN",s)==0) {
                    fprintf(out, "%s", buf[loc+3]);
                    loc = parseExpression(buf,loc+4,out,loc+4);
                    std::istringstream ss3(buf[loc]);
                    ss3>>s;
                    if(strcmp("SEMICN",s)==0) {
                        fprintf(out, "%s", buf[loc]);
                        loc = parseConditon(buf,loc+1,out,loc+1);
                        std::istringstream ss3(buf[loc]);
                        ss3>>s;
                        if(strcmp("SEMICN",s)==0) {
                            fprintf(out, "%s", buf[loc]);
                            std::istringstream ss4(buf[loc+1]);
                            ss4>>s;
                            if(strcmp("IDENFR",s)==0) {
                                fprintf(out, "%s", buf[loc+1]);
                                std::istringstream ss5(buf[loc+2]);
                                ss5>>s;
                                if(strcmp("ASSIGN",s)==0) {
                                    fprintf(out, "%s", buf[loc+2]);
                                    std::istringstream ss6(buf[loc+3]);
                                    ss6>>s;
                                     if(strcmp("IDENFR",s)==0) {
                                        fprintf(out, "%s", buf[loc+3]);
                                        std::istringstream ss7(buf[loc+4]);
                                        ss7>>s;
                                        if(strcmp("MINU",s)==0||strcmp("PLUS",s)==0) {
                                            fprintf(out, "%s", buf[loc+4]);
                                            loc = parseUnsignedInt(buf,loc+5,out);
                                            fprintf(out,  "%s\n", "<步长>");
                                            std::istringstream ss8(buf[loc]);
                                            ss8>>s;
                                            if(strcmp("RPARENT",s)==0) {
                                                fprintf(out, "%s", buf[loc]);
                                                loc = parseStmt(buf,loc+1,out,loc+1);
                                            }
                                        }
                                     }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(flag<loc){

        fprintf(out,  "%s\n", "<循环语句>");
    }
    return loc;
}

int parsePrintStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("PRINTFTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc++;
            int temp = parseString(buf,loc,out,loc);
            if(loc==temp){
                loc = parseExpression(buf,loc,out,loc);
                std::istringstream ss2(buf[loc]);
                ss2>>s;
                if(strcmp("RPARENT",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                }
            } else {
                loc = temp;
                std::istringstream ss2(buf[loc]);
                ss2>>s;
                if(strcmp("RPARENT",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                } else if(strcmp("COMMA",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                    loc = parseExpression(buf,loc,out,loc);
                    std::istringstream ss3(buf[loc]);
                    ss3>>s;
                    if(strcmp("RPARENT",s)==0) {
                        fprintf(out, "%s", buf[loc]);
                        loc++;
                    }
                }
            }


        }
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<写语句>");
    }
    return loc;
}

int parseScanStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("SCANFTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc++;
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("IDENFR",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                while(strcmp("COMMA",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                    std::istringstream ss4(buf[loc]);
                    ss4>>s;
                    if(strcmp("IDENFR",s)==0) {
                        fprintf(out, "%s", buf[loc]);
                        loc++;
                        std::istringstream ss4(buf[loc]);
                        ss4>>s;
                    } else {
                        break;
                    }
                }
                if(strcmp("RPARENT",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc++;
                }
            }
        }
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<读语句>");
    }
    return loc;
}

int parseRetStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("RETURNTK",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("LPARENT",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc++;
            loc = parseExpression(buf,loc,out,loc);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("RPARENT",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;
            }
        }
    }
    if(flag<loc) {
        fprintf(out,  "%s\n", "<返回语句>");
    }
    return loc;
}

int parseAssignStmt(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("IDENFR",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc++;
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("ASSIGN",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc = parseExpression(buf,loc+1,out,loc+1);
        } else if(strcmp("LBRACK",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc = parseExpression(buf,loc+1,out,loc+1);
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("RBRACK",s)==0) {
                fprintf(out, "%s", buf[loc]);
                loc++;
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("ASSIGN",s)==0) {
                    fprintf(out, "%s", buf[loc]);
                    loc = parseExpression(buf,loc+1,out,loc+1);
                }
            }
        }

    }

    if(flag<loc){
        fprintf(out,  "%s\n", "<赋值语句>");
    }
    return loc;
}

bool ifInVec(std::string a){
    if(vec.empty()){
        return false;
    }
    for(int i = 0;i<(int)vec.size();i++) {
        std::cout<<"vec_i:"<<vec.at(i)<<std::endl;
        if(vec.at(i)==a){
            return true;
        }
    }
    return false;
}

int parseStmt (char buf[1024][128], int loc, FILE* out,int flag) {
    int temp = parseIfStmt(buf,loc,out,loc);
    if(loc<temp){
        fprintf(out,  "%s\n", "<语句>");
        return temp;
    }
    temp = parseLoopStmt(buf,loc,out,loc);
    if(loc<temp){
        fprintf(out,  "%s\n", "<语句>");
        return temp;
    }
    std::istringstream ss(buf[loc]);
    ss>>s;
    if(strcmp("LBRACE",s)==0) {
        fprintf(out, "%s", buf[loc]);
        loc = parseStmtCol(buf,loc+1,out,loc+1,loc+1);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("RBRACE",s)==0) {
            fprintf(out, "%s", buf[loc]);
            loc++;
            if(flag<loc){
                fprintf(out,  "%s\n", "<语句>");
            }
            return loc;
        }
    }
    std::istringstream ss1(buf[loc+1]);
    ss1>>s;
    if(strcmp("ASSIGN",s)==0||strcmp("LBRACK",s)==0) {
        loc = parseAssignStmt(buf,loc,out,loc);
    }else if(strcmp("LPARENT",s)==0){
        std::istringstream ss2(buf[loc]);
        ss2>>s;
        if(strcmp("IDENFR",s)==0){
            std::string tempstr="";
            int i = 0;
            while(buf[loc][i]!='\n'&&buf[loc][i]!='\0'){
                tempstr+=buf[loc][i];
                i++;
            }
            std::cout<<"Fuck: "<<tempstr<<std::endl;
            if(!ifInVec(tempstr)) {
                loc = parseHaveNoRetCall(buf,loc,out,loc);
            }else {
                loc = parseHaveRetCall(buf,loc,out,loc);
            }
        }


    }
    loc = parsePrintStmt(buf,loc,out,loc);
    loc = parseScanStmt(buf,loc,out,loc);
    loc = parseRetStmt(buf,loc,out,loc);

    std::istringstream ss2(buf[loc]);
    ss2>>s;
    if(strcmp("SEMICN",s)==0){
        fprintf(out, "%s", buf[loc]);
        loc++;
    }
    //loc = parseHaveNoRetCall(buf,loc,out,loc);

    if(flag<loc){
        fprintf(out,  "%s\n", "<语句>");
    }
    return loc;
}

int parseStmtCol(char buf[1024][128], int loc, FILE* out,int flag,int fuck) {
    loc = parseStmt(buf,loc,out,loc);
    /*
    std::istringstream ss(buf[loc]);
    ss>>s;

    if(strcmp("LBRACE",s)==0||strcmp("WHILETK",s)==0||strcmp("FORTK",s)==0||strcmp("DOTK",s)==0||strcmp("IFTK",s)==0||strcmp("IDENFR",s)==0) {
        return parseStmtCol(buf,loc,out,flag);
    }
    */
    int temp = loc;
    if(flag!=temp){
        flag=temp;
        return parseStmtCol(buf,loc,out,loc,fuck);
    }
    if(fuck<temp){
        fprintf(out,  "%s\n", "<语句列>");
    }

    return loc;
}

int parseComplexStmt(char buf[1024][128], int loc, FILE* out) {
    loc = parseConstDes(buf,loc,out,loc);
    loc = parseVarDes(buf,loc,out,loc);
    loc = parseStmtCol(buf,loc,out,loc,loc);
    fprintf(out,  "%s\n", "<复合语句>");
    return loc;
}

int parseHaveRetFuncDef(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        loc = parseDeclareHead(buf,loc,out);
        fprintf(out, "%s", buf[loc]);
        loc = parseVarDefOrParamForm(buf,loc+1,out,2);
        std::istringstream ss1(buf[loc]);
        ss1>>s;
        if(strcmp("RPARENT",s)==0){
            fprintf(out,  "%s", buf[loc]);
            loc++;
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("LBRACE",s)==0) {
                fprintf(out,  "%s", buf[loc]);
                loc = parseComplexStmt(buf,loc+1,out);
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("RBRACE",s)==0) {
                    fprintf(out,  "%s", buf[loc]);
                    loc++;
                }
            }
        }
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<有返回值函数定义>");
    }
    return loc;
}

int parseMainFunc(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("MAINTK",s)==0){
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("VOIDTK",s)==0) {
                fprintf(out,  "%s", buf[loc]);
                fprintf(out,  "%s", buf[loc+1]);
                fprintf(out,  "%s", buf[loc+2]);
                loc+=3;
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("RPARENT",s)==0){
                    fprintf(out,  "%s", buf[loc]);
                    loc++;
                    std::istringstream ss4(buf[loc]);
                    ss4>>s;
                    if(strcmp("LBRACE",s)==0) {
                        fprintf(out,  "%s", buf[loc]);
                        loc = parseComplexStmt(buf,loc+1,out);
                        std::istringstream ss5(buf[loc]);
                        ss5>>s;
                        if(strcmp("RBRACE",s)==0) {
                            fprintf(out,  "%s", buf[loc]);
                            loc++;
                        }
                    }
                }
            }
        }
        //main
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<主函数>");
    }
    return loc;
}

int parseHaveNoRetFuncDef(char buf[1024][128], int loc, FILE* out,int flag) {
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0){
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("VOIDTK",s)==0) {
                fprintf(out,  "%s", buf[loc]);
                fprintf(out,  "%s", buf[loc+1]);
                fprintf(out,  "%s", buf[loc+2]);
                loc = parseVarDefOrParamForm(buf,loc+3,out,2);
                std::istringstream ss3(buf[loc]);
                ss3>>s;
                if(strcmp("RPARENT",s)==0){
                    fprintf(out,  "%s", buf[loc]);
                    loc++;
                    std::istringstream ss4(buf[loc]);
                    ss4>>s;
                    if(strcmp("LBRACE",s)==0) {
                        fprintf(out,  "%s", buf[loc]);
                        loc = parseComplexStmt(buf,loc+1,out);
                        std::istringstream ss5(buf[loc]);
                        ss5>>s;
                        if(strcmp("RBRACE",s)==0) {
                            fprintf(out,  "%s", buf[loc]);
                            loc++;
                        }
                    }
                }
            }
        }
        //main
    }
    if(flag<loc){
        fprintf(out,  "%s\n", "<无返回值函数定义>");
    }
    return loc;
}
int parseHaveRetFunc(char buf[1024][128], int loc, FILE* out,int flag);

int parseHaveNoRetFunc(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseHaveNoRetFuncDef(buf,loc,out,loc);
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0){
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("VOIDTK",s)==0) {
                return parseHaveNoRetFunc(buf,loc,out,loc);
            } else if(strcmp("INTTK",s)==0||strcmp("CHARTK",s)==0) {
                return parseHaveRetFunc(buf,loc,out,loc);
            }
        }
    }
    return loc;
}

int parseHaveRetFunc(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseHaveRetFuncDef(buf,loc,out,loc);
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0){
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("VOIDTK",s)==0) {
                return parseHaveNoRetFunc(buf,loc,out,loc);
            }
            else if(strcmp("INTTK",s)==0||strcmp("CHARTK",s)==0) {
                return parseHaveRetFunc(buf,loc,out,loc);
            }
        }
    }
    return loc;
}

int parseProgram(char buf[1024][128], int loc, FILE* out,int flag) {
    loc = parseConstDes(buf,loc,out,loc);
    loc = parseVarDes(buf,loc,out,loc);
    std::istringstream ss(buf[loc+2]);
    ss>>s;
    if(strcmp("LPARENT",s)==0) {
        std::istringstream ss1(buf[loc+1]);
        ss1>>s;
        if(strcmp("IDENFR",s)==0){
            std::istringstream ss2(buf[loc]);
            ss2>>s;
            if(strcmp("VOIDTK",s)==0) {
                loc = parseHaveNoRetFunc(buf,loc,out,loc);
            }else if(strcmp("INTTK",s)==0||strcmp("CHARTK",s)==0) {
                loc = parseHaveRetFunc(buf,loc,out,loc);
            }
        }
    }
    loc = parseMainFunc(buf,loc,out,loc);
    fprintf(out,  "%s\n", "<程序>");
    return loc;
}


int main()
{
/**/
	if(lex()){
        FILE	* fp;
        FILE    * out;
        fp	= fopen( "output.txt", "r" );
        char BUFFER[1024][128];
        int i=0;

        while(fgets(BUFFER[i],sizeof(BUFFER[i]),fp)!=NULL)
        {
            //std::cout<<BUFFER[i];
            i++;

        }
        fclose(fp);
        out = fopen( "output.txt", "w+" );

        int tempa=parseProgram(BUFFER,0,out,0);
        std::cout<<tempa<<std::endl;
        fclose(out);
        std::cout<<i;
	}



	return(0);
}
