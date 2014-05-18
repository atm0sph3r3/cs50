<?php
    require("../includes/config.php");
    
    //User is searching for a stock
    if($_SERVER['REQUEST_METHOD'] == "POST"){
        extract($_POST);
        $quote = lookup($symbol);
        if($quote !== false){
            extract($quote);
            render("stock_result.php", array("symbol"=>$symbol, "name"=>$name, "price"=>$price, "title"=>"{$symbol} information"));
        } else {
            render("stock_result.php",array("title"=>"No results to display."));
        }
    } else {
        render("stock_lookup.php",array("title"=>"Look-up Stock Price"));
    }