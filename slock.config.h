/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nobody";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "#14161b",   /* after initialization */
	[INPUT] =  "#4a678d",   /* during input */
	[FAILED] = "#644138",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;
