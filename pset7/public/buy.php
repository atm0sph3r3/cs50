<?php
    require("../includes/config.php");
    
    if($_SERVER["REQUEST_METHOD"] == "POST"){
        //Integers only
        if(isset($_POST["shares"]) && isset($_POST["symbol"])){
            if(preg_match("/^\d+$/",$_POST["shares"])){
                $shares = $_POST["shares"];
                $symbol = strtoupper($_POST["symbol"]);

                $lookup = lookup($symbol);
                if($lookup !== FALSE){
                    $cashBalance = $user->cashBalance();
                    $cost = (float)$lookup["price"] * (int)$shares;
                    //Ensure user has enough money
                    if($cashBalance >= $cost){
                        //Purchase stock and update balance
                        $user->purchaseStock($symbol,$shares);
                        $user->updateBalance($cost);
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
