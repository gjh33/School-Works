datatype transactions =
	 Withdraw of int | Deposit of int | Check_balance;

fun make_account (opening_balance: int, setpass:string) =
    let
	val balance = ref opening_balance;
	val pswd = ref setpass;
    in
	fn (trans: transactions, pass:string) =>
	   if (pass = !pswd)
	   then
	       case trans of
		   Withdraw(a)
		   => ((balance := !balance-a); !balance)
		 | Deposit(a)
		   => ((balance := !balance+a); !balance)
		 | Check_balance
		   => (!balance)
	   else
	       (print ("Wrong password.\n"); 0)
    end;
