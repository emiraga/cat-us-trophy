vector<pair<pii,pii> > L;
REP(i,9) { D(i);
	L.clear();
	REP(j,1000 * 1000) L.push_back( make_pair( pii(rand(),rand()), pii(rand(),rand())));
	sort(ALL(L));
}
