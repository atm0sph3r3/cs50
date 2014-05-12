<?php

//Generates array that has all porfolio information (name, symbol, shares, current price)
function generatePortfolio(){
    $userID = $_SESSION['id'];
    //Retrieve user's stock info
    $query = "SELECT * FROM accounts WHERE id=?";
    $results = query($query,$userID);
    $returnResults = array();
    foreach($results as $result){
        $temp = array();
        $temp["symbol"] = $result["symbol"];
        $temp["shares"] = $result["shares"];
        $lookupResults  = lookup($result["symbol"]);
        if($lookupResults !== false){
            $temp["name"] = $lookupResults["name"];
            $temp["price"] = $lookupResults["price"];
        } else {
            break;
        }
        array_push($returnResults, $temp);
    }
   return $returnResults;
}