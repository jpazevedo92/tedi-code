<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class MplsTag extends Model
{
    public function uav()
    {
        return $this->belongsTo('Uav' , 'id');
    }
}
