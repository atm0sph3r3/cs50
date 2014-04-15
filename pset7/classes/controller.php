<?php
/**
 * Description of Controller
 *
 * @author dev
 */
abstract class Controller {
    
    public $model = null;
       
    public function __construct() {
        //no code
    }
    
    //Method all derived class implement
    public abstract function index();
}
