<?php

/**
 * Description of quote
 *
 * @author dev
 */
class Quote extends Controller{
    
    //Create instance of the model
    public function __construct() {
        $this->model = new quoteModel();
    }
    
    public function index() {
        render("quote.php",array("title"=>"Get a Quote"));
    }
    
    public function search($stock){

    }
}
