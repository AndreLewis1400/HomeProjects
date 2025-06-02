/*
 * Author: Andre Lewis
 * Location: Home
 * Date: 04/26/2024
 * 
 */

#include <stdio.h>
#include <stdbool.h>

int main()
{
	enum Company {GOOGLE = 2, FACEBOOK, XEROX = 0, YAHOO, EBAY = 4, MICROSOFT};
	
	enum Company xerox = XEROX;
	enum Company google = GOOGLE;
	enum Company ebay = EBAY;
	
	printf("The value of google: %d\nThe Value of xerox: %d\nThe value of ebay: %d", google, xerox, ebay);
		
	return 0;
}
