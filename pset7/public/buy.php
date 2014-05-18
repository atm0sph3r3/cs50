<?php
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "POST"){
        extract($_POST);
        //Integers only
        if(!empty($shares) && !empty($symbol)){
            if(preg_match("/^\d+$/",$shares)){
                $symbol = strtoupper($symbol);
                
                //Lookup symbol
                $lookup = lookup($symbol);
                if($lookup !== FALSE){
                    extract($lookup);
                    $cashBalance = $user->cashBalance();
                    $cost = (float)$price * (int)$shares;
                    //Ensure user has enough money
                    if($cashBalance >= $cost){
                        //Purchase stock and update balance
                        $user->buy($symbol,$shares,$lookup["price"]);
                        render("bought_stock.php",array("title"=>"Results of purchase","results"=>array("cost"=>$cost, "symbol"=>$symbol,"price"=>$lookup["price"],"shares"=>$shares)));
                    } else {
                        apologize("You do not have enough money for this purchase.");
                    }
                } else {
                    apologize("You've entered an invalid stock.");
                }
            } else {
                apologize("Please enter integers only.");
            }
        } else {
            apologize("Both symbol and shares must be filled in.");
        }
    } else {
        render("buy_stock.php",array("title"=>"Purchase stock"));
    }
