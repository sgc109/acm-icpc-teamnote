const int MAX_C = 26;

class AhoCorasick{
public:
	struct trie{
		trie* next[MAX_C];
		trie* fail;
		int output;
		trie(){
			for(int i = 0; i < MAX_C; i++) next[i] = NULL;
			fail = NULL;
			output = 0;
		}
		~trie(){
			for(int i = 0; i < MAX_C; i++){
				if(next[i]) delete next[i];
			}
		}
		void insert(string& s, int index){
			trie *curr = this;
			int sz = s.size();
			for(int i = 0; i < sz; i++){
				int v = s[i] - 'a';
				if(!curr->next[v]) curr->next[v] = new trie();
				curr = curr->next[v];
			}
			curr->output = index;
		}
	};
	trie *root;
	AhoCorasick(vector<string>& arr){
		root = new trie();
		root->fail = root;
		int sz = arr.size();
		for(int i = 0; i < sz; i++) root->insert(arr[i], i + 1);
		queue<trie*> q;
		q.push(root);
		while(!q.empty()){
			trie *curr = q.front();
			q.pop();
			for(int i = 0; i < MAX_C; i++){
				trie *next = curr->next[i];
				if(!next) continue;
				trie *dest = curr->fail;
				while(dest != root && !dest->next[i]) dest = dest->fail;
				if(curr != root && dest->next[i]) dest = dest->next[i];
				next->fail = dest;
				if(next->fail->output) next->output = next->fail->output;
				q.push(next);
			}
		}
	}
	~AhoCorasick(){
		delete root;
	}
	bool isExist(string &s){
		trie *curr = root;
		int sz = s.size();
		for(int i = 0; i < sz; i++){
			int v = s[i] - 'a';
			while(curr != root && !curr->next[v]) curr = curr->fail;
			if(curr->next[v]) curr = curr->next[v];
			if(!curr->output) continue;
			return true;
		}
		return false;
	}
	vector<pair<int, int>> getPos(string &s){
		vector<pair<int, int>> res;
		trie *curr = root;
		int sz = s.size();
		for(int i = 0; i < sz; i++){
			int v = s[i] - 'a';
			while(curr != root && !curr->next[v]) curr = curr->fail;
			if(curr->next[v]) curr = curr->next[v];
			if(!curr->output) continue;
			res.push_back({i, curr->output});
		}
		return res;
	}
};
