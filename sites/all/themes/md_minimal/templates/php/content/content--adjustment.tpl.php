<?php

$file = fopen(DRUPAL_ROOT . '/transform.json', 'r'); $json = fgets($file); fclose($file);

$press_quotes = json_decode($json);

$params = $_POST;

function iteratethis($nid, $prop) {
    global $press_quotes;
    foreach($press_quotes as $quote) {
        if($quote->primarynid === (int) $nid) {
            return $quote->{$prop};
        }
    }
}

function save_pressquotes($agency, $nid) {
    
    try {
        $tv = db_select('taxonomy_vocabulary', 'tv')->fields('tv', array('vid'))->condition('tv.machine_name', 'agency')->execute()->fetchObject();
        $term = new stdClass();
        $term->vid = $tv->vid;
        $term->name = $agency;
        taxonomy_term_save($term);
        $term2 = taxonomy_term_load($term->tid);
        $items = (array) $term2->field_agency_type;
        $file = fopen(DRUPAL_ROOT . '/file.txt', 'w+'); fwrite($file, (string) $items); fclose($file);
        $term2->field_agency_type['und'][0]['value'] = 'quote';
        $instance = field_read_instance('taxonomy_term', 'field_agency_type', 'agency');
        $field_id = $instance['field_id'];
        field_sql_storage_field_storage_write('taxonomy_term', $term2, FIELD_STORAGE_INSERT, array($field_id));
        
        global $params;
        
        db_insert('dcc_quotes')->fields(array(
            'nid' => iteratethis($nid, 'nid'),
            'quote' => iteratethis($nid, 'body'),
            'quote_by_tid' => $term2->tid,
            'author_name' => !empty($params['author_name']) ? $params['author_name'] : NULL
        ))->execute();
        
    } catch (Exception $e) {
        $file = fopen(DRUPAL_ROOT . '/file.txt', 'a+'); fwrite($file, '\n' . $e->getTraceAsString()); fclose($file);
    }
        
}

?>

<form action="/boot.php" method="POST">
    <div class="clearfix">
        <?php foreach($press_quotes as $quote): ?>
        <div class="span3">
            <input type="checkbox" name="<?php echo 'quote_' . $quote->primarynid; ?>" value="checkbox_1" />
            <input type="hidden" name="<?php echo 'title_' . $quote->primarynid; ?>" value="<?php echo $quote->title; ?>" />
            <span><?php echo $quote->title; ?></span>
        </div>
        <?php endforeach; ?>
    </div>
    <div>
        <label>Agency</label>
        <input type="textbox" name="Agency_Name" value="" />
    </div>
    <div>
        <label>Author</label>
        <input type="textbox" name="author_name" value="" />
    </div>
    <button type="submit">Submit</button>
</form>

<script type="text/javascript">
    (function($){
        $(document).ready(function() {
            
        });
    })(jQuery);
</script>


<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

//class MyJSONArrayIterate implements Iterator {
//    
//    private $position;
//    private $JSONArray;
//    
//    public function __construct($array) {
//        $this->JSONArray = $array;
//    }
//    
//    public function iteratethis($nid, $prop) {
//        
//        
//        
//    }
//    
//    public function current() {
//        return $this->JSONArray[$this->position];
//    }
//    
//    public function next() {
//        ++$this->position;
//    }
//    
//    public function rewind() {
//        $this->position = 0;
//    }
//    
//    public function key() {
//        return $this->position;
//    }
//    
//    public function valid() {
//        return gettype($this->position) === 'integer';
//    }
//    
//}

if(!empty($params)) {
    $transaction = db_transaction();
    try {
        foreach($params as $param => $value) {
            if($value === 'checkbox_1' && strpos($param, 'quote_') == 0) {
                $nid = (int) str_replace('quote_', '', $param);
                if($params['Agency_Name'] == 'NULL') {
                    $params['Agency_Name'] = NULL;
                } elseif(empty($params['Agency_Name'])) {
                    $params['Agency_Name'] = $params['title_' . $nid];
                }
                save_pressquotes($params['Agency_Name'], $nid);
            }
        }
    } catch (Exception $e) {
        $file = fopen(DRUPAL_ROOT . '/file.txt', 'a+'); fwrite($file, '\n' . $e->getTraceAsString()); fclose($file);
        $transaction->rollback();
    }
}

?>