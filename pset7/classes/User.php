<?php
/**
 * Description of User
 *
 * @author jharvard
 */

require("Account.php");

class User {
    
    private $id;
    private static $user;
    private $cashBalance;
    private $account;
    
    private function __construct() {
        $this->id = $_SESSION['id'];
        $this->account = new Account();
    }
    
    public static function getUser(){
        if(self::$user === NULL){
            self::$user = new User();
        }
        return self::$user;
    }
    
    //return cash currently in account
    public function cashBalance(){
        $result = query("SELECT cash FROM users WHERE id = ?", $this->id);
        return (float)$result[0]["cash"];
    }
        
    //Return user's portfolio using member attribute
    public function portfolio(){
        return $this->account->generatePortfolio($this->id);
    }
    
    //Return portfolio balnace at the time of call
    public function portfolioValue(){
        return $this->account->portfolioBalance($this->id);
    }
    
    //Return an array of stocks the user wishes to sell
    public function sell(){
        $stocksToSell = array();
        //Return array with stocks sold and the cash gained
        $stocksSold = array();
        while($element = current($_POST)){
            if($element == "on"){
                array_push($stocksToSell, key($_POST));
            }
            next($_POST);
        }
        //Retrieve stock info from owner's portfolio
        $portfolio = $this->portfolio();
        //Ensure user actually owns the stock that they want to sell
        while($sellStock = current($stocksToSell)){
            foreach($portfolio as $ownStock){
                if($ownStock['symbol'] == $sellStock){
                    $lookup = lookup($sellStock);
                    $value = (float)$ownStock["shares"] * (float)$lookup["price"];
                    //Remove stock from portfolio and update balance
                    $this->account->sell($this->id,$sellStock,$ownStock["shares"],$lookup["price"]);
                    $this->updateBalance($value);
                    $stocksSold[$sellStock] = $value;
                    break;
                }
            }
            next($stocksToSell);
        }//while
        return $stocksSold;
    }
    
    public function updateBalance($amount){
        query("UPDATE users SET cash = ? WHERE id = ?", ($this->cashBalance() + (float)$amount),$this->id);
    }
    
    public function buy($stock,$shares,$price){
        $this->account->buy($this->id, $stock, $shares,$price);
    }
    
    public function history(){
        return $this->account->history($this->id);
    }
    
    public function info(){
        return query("SELECT * FROM users WHERE id=?",$this->id);
    }
    
    public function changePassword($newPassword){
        query("UPDATE users SET hash=? WHERE id=?", crypt($newPassword), $this->id);
    }
}
