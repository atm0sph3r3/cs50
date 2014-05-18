<?php
/**
 * Describes an account
 *
 * @author jharvard
 */
class Account {
    public function generatePortfolio($userID){
        //Retrieve user's stock info
        $results = query("SELECT * FROM accounts WHERE id=?",$userID);
        $returnResults = array();
        $balance = 0;
        foreach($results as $result){
            extract($result);
            $temp = array();
            $temp["symbol"] = $symbol;
            $temp["shares"] = $shares;
            $lookupResults  = lookup($symbol);
            extract($lookupResults);
            $temp["name"] = $name;
            $temp["price"] = $price;
            $temp["value"] = (float)$price * (float)$shares;
            $balance += $temp["value"];
            array_push($returnResults, $temp);
        }
        $returnResults["balance"] = $balance;
        
        return $returnResults;
    }
    
    public function sell($userId, $symbol,$shares,$price){
        query("DELETE FROM accounts WHERE id = ? AND symbol = ?",$userId, $symbol);
        $this->recordTransaction($userId, $symbol, $shares, $price, "SELL");
    }
    
    public function buy($userId, $symbol, $shares,$price){
        query("INSERT INTO accounts (id,symbol,shares) VALUES (?,?,?) ON DUPLICATE KEY UPDATE shares = shares + ?",$userId,$symbol,$shares,$shares);
        $this->recordTransaction($userId, $symbol, $shares, $price, "BUY");
    }
    
    private function recordTransaction($userId,$symbol,$shares,$price,$type){
        query("INSERT INTO transactions (id,symbol,shares,price,date,type) VALUES (?,?,?,?,?,?)",$userId,$symbol,$shares,$price,time(),$type);
    }
    
    public function history($userId){
        return $history = query("SELECT * FROM transactions WHERE id = ?", $userId);
    }
}
