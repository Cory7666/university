flush-chains:
	iptables -F INPUT
	iptables -F OUTPUT
	iptables -P INPUT ACCEPT

allow-stateful-tcp:
	iptables -A INPUT  -m state --state RELATED,ESTABLISHED -j ACCEPT
	iptables -A OUTPUT -m state --state RELATED,ESTABLISHED -j ACCEPT

allow-http-conn:
	iptables -A INPUT -p tcp --dport 80  -j ACCEPT
	iptables -A INPUT -p tcp --dport 443 -j ACCEPT

allow-ssh-conn:
	iptables -A INPUT -p tcp --dport 22 -j ACCEPT

allow-subnets:
	iptables -A INPUT -i lo -j ACCEPT
	iptables -A INPUT -s 172.150.0.0/24 -j ACCEPT

guard: flush-chains allow-subnets allow-stateful-tcp allow-http-conn # allow-ssh-conn
	iptables -P INPUT DROP

list-rules:
	iptables -L --line-numbers -n
