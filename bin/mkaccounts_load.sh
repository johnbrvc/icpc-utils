#!/bin/bash
echo 'site	account	displayname	password	group	permdisplay	permlogin	externalid	alias	permpassword	longschoolname	shortschoolname	countrycode'
team=55
while read alias password
do
	extid=$((1100+team))
	echo -e "1\tteam$team\t$alias\t$password\t\tfalse\ttrue\t$extid\t$alias\tfalse\t\t\tXXX"
	team=$((team+1))
done < /tmp/ddd

#1	team150	team150	team150		false	true	1150	domjudge	false			XXX
#1	team151	team151	team151		false	true	1151	cds	false			XXX
#1	team152	team152	team152		false	true	1152	pc2	false			XXX
#1	team153	team153	team153		false	true	1153	operations	false			XXX
#1	team154	team154	team154		false	true	1154	sysops	false			XXX
#1	team155	team155	team155		false	true	1155	yujie	false			XXX
#1	team156	team156	team156		false	true	1156	bonomo	false			XXX
#1	team157	team157	team157		false	true	1157	walter	false			XXX
#1	team158	team158	team158		false	true	1158	derek	false			XXX
#1	team159	team159	team159		false	true	1159	jo	false			XXX
#1	team160	team160	team160		false	true	1160	matthias	false			XXX
#1	team161	team161	team161		false	true	1161	arknave	false			XXX
#1	team162	team162	team162		false	true	1162	per	false			XXX
#1	team163	team163	team163		false	true	1163	martin	false			XXX
#1	team164	team164	team164		false	true	1164	onufry	false			XXX
#1	team165	team165	team165		false	true	1165	bob	false			XXX
#1	team166	team166	team166		false	true	1166	paul	false			XXX
#1	team167	team167	team167		false	true	1167	federico	false			XXX
#1	team168	team168	team168		false	true	1168	michal	false			XXX
#1	team169	team169	team169		false	true	1169	nicky	false			XXX
#1	team170	team170	team170		false	true	1170	eldering	false			XXX
#1	team171	team171	team171		false	true	1171	michael	false			XXX
#1	team172	team172	team172		false	true	1172	kevinjil	false			XXX
#1	team173	team173	team173		false	true	1173	edomora97	false			XXX
#1	team174	team174	team174		false	true	1174	brinky	false			XXX
#1	team175	team175	team175		false	true	1175	tobi	false			XXX
#1	team176	team176	team176		false	true	1176	tuupke	false			XXX
#1	team177	team177	team177		false	true	1177	ubergeek42	false			XXX
