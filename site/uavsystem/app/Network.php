<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Network extends Model
{
    public function device()
    {
        return $this->hasOne(Device::class);
    }
}
