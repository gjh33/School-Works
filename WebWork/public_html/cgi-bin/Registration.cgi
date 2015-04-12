#!/usr/bin/perl

use CGI ':standard';

print "Content-type: text/html\n\n";

my $name = param('name');
my $useri = param('usr');
my $pass = param('pswd');

open(USERS, "<data/members.CSV");
my @users = <USERS>;
close(USERS);

$isValid = 1;

foreach $user (@users) {
	my @data = split(/ /, $user);
	if ($useri eq $data[1])
	{
		$isValid = 0;
	}
}

if ($isValid) {
	open(ACC, ">>data/members.CSV");
	print ACC "$name $useri $pass\n";
	close (ACC);
	print "<html><head><title>Register Success</title></head><body><h3>Successful Registration of $name</h3><br><a href=\"http://cs.mcgill.ca/~sarres/welcome.html\">Return to Login</a></body></html>";
}
else {
	print "<html><head><title>Invalid User</title></head><body><h3>Username $useri is already taken</h3><br><a href=\"http://cs.mcgill.ca/~ljones15/register.html\">Try Again?</a><br><a href=\"http://cs.mcgill.ca/~sarres/welcome.html\">Go Home</a></body></html>";
}
exit 0;
