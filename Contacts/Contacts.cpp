// Contacts.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <vector>
#include<stdio.h>
#include <direct.h>
#include <stdio.h>
#include <errno.h>

#pragma warning(disable:4996)
#include "myvector.h"
#include "global.h"
#include "db.h"
#include "server.h"
#include "head.h"

#include "authentication.h"
#include "string_utils.h"
#include "utils.h"
#include "contact_utils.h"
#include "menu_utils.h"


using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	show_authentication_menu();
	return 0;
}

