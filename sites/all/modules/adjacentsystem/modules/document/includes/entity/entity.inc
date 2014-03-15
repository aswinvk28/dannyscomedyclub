<?php 

class DocumentEntity extends CommonEntity {
    const file_path = 'documents/';
    var $file_path;
    var $file_type;
    var $document_id;
    var $document_file_id;
    var $document_author;
    private $file;
    private $document_body;
    
    public function getDocumentBody() {
        if(empty($this->document_body)) {
            if(isset($this->file_type)) {
                $method = 'get_'.$this->file_type[1];
                $this->document_body = $this->{$method}();
            }
        }
        return $this->document_body;
    }
    
    private function get_html() {
        $file_id = $this->getFile();
        if(!is_null($file_id)) {
            $file = file_load($this->getFile());
            if(!empty($file)) {
                $path = str_replace('public:/', DRUPAL_ROOT.base_path().variable_get('file_public_path', 'sites/default/files'), $file->uri);
                $handle = fopen($path, "rt");
                $contents = fread($handle, filesize($path));
                fclose($handle);
                return $contents;
            }
        }
        
        return '';
    }
    
    public function getFile() {
        return $this->document_file_id;
    }
    
    public function createFile($body) {
        global $user;
        $this->file = new stdClass();
        $this->file->filemime = $this->file_type[0];
        $this->file->filename = $this->file_path.'_'.str_replace('.', '', microtime(true)).'.'.$this->file_type[1];
        $this->file->uri = 'public://'.self::file_path.$this->file_path.'/'.$this->file->filename;
        $this->file->uid = $user->uid;
        $this->file->status = 1;
        $this->saveFile($body);
    }
    
    public function saveFile($body) {
        if(empty($body)) return FALSE;
        if(!is_null($this->getFile())) {
            $this->file = file_load($this->getFile());
        }
        if(isset($this->file)) {
            $destination = str_replace('public:/', DRUPAL_ROOT.base_path().variable_get('file_public_path', 'sites/default/files'), $this->file->uri);
            if($destination) {
                if(isset($this->file_type)) {
                    $method = 'write_'.$this->file_type[1];
                    if($this->{$method}($destination, $body)) {
                        if(!isset($this->file->fid)) {
                            $this->file = file_save($this->file);
                        }
                        $this->document_file_id = $this->file->fid;
                    }
                }
            }
        }
        
        return $this->getFile();
    }
    
    private function write_html($destination, $body) {
        return file_put_contents($destination, $body);
    }
    
    public function getAuthor() {
        return $this->document_author;
    }
}

?>