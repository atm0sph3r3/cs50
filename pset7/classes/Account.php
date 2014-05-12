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
            $temp = array();
            $temp["symbol"] = $result["symbol"];
            $temp["shares"] = $result["shares"];
            $lookupResults  = lookup($result["symbol"]);
            $temp["name"] = $lookupResults["name"];
            $temp["price"] = $lookupResults["price"];
            $temp["value"] = (float)$lookupResults["price"] * (float)$result["shares"];
            $balance += $temp["value"];
            array_push($returnResults, $temp);
        }
        $returnResults["balance"] = $balance;
        
        return $returnResults;
    }
    
    public function removeStock($userId, $stock){
        query("DELETE FROM accounts WHERE id = ? AND symbol = ?",$userId, $stock);
    }
}
