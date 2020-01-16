<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Route extends Model
{
    public function uav()
    {
    	return $this->belongsTo(Uav::class);
    }
}
